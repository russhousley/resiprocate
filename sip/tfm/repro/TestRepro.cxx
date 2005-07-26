#include "repro/BerkeleyDb.hxx"
#include "repro/ReproServerAuthManager.hxx"
#include "repro/monkeys/AmIResponsible.hxx"
#include "repro/monkeys/DigestAuthenticator.hxx"
#include "repro/monkeys/IsTrustedNode.hxx"
#include "repro/monkeys/LocationServer.hxx"
#include "repro/monkeys/StaticRoute.hxx"
#include "repro/monkeys/StrictRouteFixup.hxx"
#include "resiprocate/os/Logger.hxx"
#include "tfm/repro/TestRepro.hxx"

using namespace resip;
using namespace repro;



#define RESIPROCATE_SUBSYSTEM resip::Subsystem::TEST

static RequestProcessorChain&  
makeRequestProcessorChain(RequestProcessorChain& chain, RouteStore& store)
{
   // Either the chainName is default or we don't know about it
   // Use default if we don't recognize the name
   // Should log about it.
   RequestProcessorChain* locators = new RequestProcessorChain();
   
   StrictRouteFixup* srf = new StrictRouteFixup;
   locators->addProcessor(std::auto_ptr<RequestProcessor>(srf));

   IsTrustedNode* isTrusted = new IsTrustedNode;
   locators->addProcessor(std::auto_ptr<RequestProcessor>(isTrusted));

   DigestAuthenticator* da = new DigestAuthenticator;
   chain.addProcessor(std::auto_ptr<RequestProcessor>(da)); 

   AmIResponsible* isme = new AmIResponsible;
   locators->addProcessor(std::auto_ptr<RequestProcessor>(isme));
      
   StaticRoute* sr = new StaticRoute(store);
   locators->addProcessor(std::auto_ptr<RequestProcessor>(sr));
 
   InMemoryRegistrationDatabase regData;
   LocationServer* ls = new LocationServer(regData);
   locators->addProcessor(std::auto_ptr<RequestProcessor>(ls));
 
   chain.addProcessor(std::auto_ptr<RequestProcessor>(locators));
   return chain;
}

TestRepro::TestRepro(const resip::Data& name,
                     const resip::Data& host, 
                     int port, 
                     const resip::Data& interface) : 
   TestProxy(name, host, port, interface),
   mStack(),
   mStackThread(mStack),
   mRegistrar(),
   mProfile(new MasterProfile),
   mDb(new BerkeleyDb),
   mStore(*mDb),
   mRequestProcessors(),
   mProxy(mStack, makeRequestProcessorChain(mRequestProcessors, mStore.mRouteStore), mStore.mUserStore),
   mRegData(),
   mDum(mStack),
   mDumThread(mDum)
{
   mStack.addTransport(UDP, port, V4);
   mStack.addTransport(TCP, port, V4);
   mProxy.addDomain(host);
   
   mProfile->clearSupportedMethods();
   mProfile->addSupportedMethod(resip::REGISTER);
   //mProfile->addSupportedScheme(Symbols::Sips);

   mDum.setMasterProfile(mProfile);
   mDum.setServerRegistrationHandler(&mRegistrar);
   mDum.setRegistrationPersistenceManager(&mRegData);
   mDum.addDomain(host);
   
   // Install rules so that the registrar only gets REGISTERs
   resip::MessageFilterRule::MethodList methodList;
   methodList.push_back(resip::REGISTER);

   resip::MessageFilterRuleList ruleList;
   ruleList.push_back(MessageFilterRule(resip::MessageFilterRule::SchemeList(),
                                        resip::MessageFilterRule::Any,
                                        methodList) );
   mDum.setMessageFilterRuleList(ruleList);
    
   std::auto_ptr<ServerAuthManager> authMgr(new ReproServerAuthManager(mDum, mStore.mUserStore ));
   mDum.setServerAuthManager(authMgr);    

   mStack.registerTransactionUser(mProxy);

   mStackThread.run();
   mProxy.run();
   mDumThread.run();

   run();
}

TestRepro::~TestRepro()
{
}

void
TestRepro::thread()
{
   while (!waitForShutdown(100))
   {
   }
}

void
TestRepro::addUser(const Data& userid, const Uri& aor, const Data& password)
{
   InfoLog (<< "Repro::addUser: " << userid << " " << aor);
   mStore.mUserStore.addUser(userid,aor.host(),aor.host(), password, Data::from(aor), Data::from(aor));
}

void
TestRepro::deleteUser(const Data& userid)
{
   InfoLog (<< "Repro::delUser: " << userid);
   mStore.mUserStore.eraseUser(userid);
}
