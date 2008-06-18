#include <cassert>
#include "DumFeatureMessage.hxx"
#include "rutil/WinLeakCheck.hxx"
#include "resip/dum/BaseUsage.hxx"

using namespace resip;

DumFeatureMessage::DumFeatureMessage(const Data& tid)
   : mTransactionId(tid)
{}

DumFeatureMessage::DumFeatureMessage(const DumFeatureMessage& source)
   : mTransactionId(source.mTransactionId)
{}

DumFeatureMessage::~DumFeatureMessage()
{}

Message*
DumFeatureMessage::clone() const
{
   return new DumFeatureMessage(*this);
}
            
std::ostream&
DumFeatureMessage::encodeBrief(std::ostream& strm) const
{
   return encode(strm);
}

std::ostream& 
DumFeatureMessage::encode(std::ostream& strm) const
{
   strm << "DumFeatureMessage::" << mTransactionId;
   return strm;
}