#ifndef _MessageStructs_h_
#define _MessageStructs_h_

#include "p2p/s2c/s2c/s2c_native.hxx"

namespace s2c {

typedef enum {
   bool_false = 0,
   bool_true = 1
} Boolean;

class NodeIdStruct : public PDU {
public:
   NodeIdStruct();
   unsigned char                 mId[16];


   PDUMemberFunctions
};


class ResourceIdStruct : public PDU {
public:
   ResourceIdStruct();
   std::vector<unsigned char>    mId;


   PDUMemberFunctions
};


typedef enum {
   reserved_addr = 0,
   ipv4_address = 1,
   ipv6_address = 2
} AddressType;

class IPv4AddrPortStruct : public PDU {
public:
   IPv4AddrPortStruct();
   UInt32                        mAddr;
   UInt16                        mPort;


   PDUMemberFunctions
};


class IPv6AddrPortStruct : public PDU {
public:
   IPv6AddrPortStruct();
   unsigned char                 mAddr[16];
   UInt16                        mPort;


   PDUMemberFunctions
};


class IpAddressAndPortStruct : public PDU {
public:
   IpAddressAndPortStruct();
   AddressType                   mType;
   UInt8                         mLength;
   struct {
        IPv4AddrPortStruct*           mV4addrPort;
   } mIpv4Address;
   struct {
        IPv6AddrPortStruct*           mV6addrPort;
   } mIpv6Address;


   PDUMemberFunctions
};


typedef enum {
   reserved_destination = 0,
   peer = 1,
   resource = 2,
   compressed = 3
} DestinationType;

class DestinationStruct : public PDU {
public:
   DestinationStruct();
   DestinationType               mType;
   UInt8                         mLength;
   struct {
        NodeIdStruct*                 mNodeId;
   } mPeer;
   struct {
        ResourceIdStruct*             mResourceId;
   } mResource;
   struct {
        std::vector<unsigned char>    mCompressedId;
   } mCompressed;


   PDUMemberFunctions
};


typedef enum {
   reserved1 = 0,
   signer_identity_peer = 1,
   signer_identity_name = 2,
   signer_identity_certificate = 3
} SignerIdentityType;

class SignerIdentityStruct : public PDU {
public:
   SignerIdentityStruct();
   SignerIdentityType            mIdentityType;
   std::vector<unsigned char>    mSignerIdentity;


   PDUMemberFunctions
};


class SignatureAndHashAlgorithmStruct : public PDU {
public:
   SignatureAndHashAlgorithmStruct();
   UInt8                         mSig;
   UInt8                         mHash;


   PDUMemberFunctions
};


class SignatureStruct : public PDU {
public:
   SignatureStruct();
   SignatureAndHashAlgorithmStruct*  mAlgorithm;
   SignerIdentityStruct*         mIdentity;
   std::vector<unsigned char>    mSignatureValue;


   PDUMemberFunctions
};


class ForwardingHeaderStruct : public PDU {
public:
   ForwardingHeaderStruct();
   UInt8                         mReloToken;
   UInt32                        mOverlay;
   UInt8                         mTtl;
   UInt8                         mReserved;
   UInt16                        mFragment;
   UInt8                         mVersion;
   UInt32                        mLength;
   UInt64                        mTransactionId;
   UInt16                        mFlags;
   std::vector<DestinationStruct*>  mViaList;
   std::vector<DestinationStruct*>  mDestinationList;
   UInt16                        mRouteLogLenDummy;
   UInt16                        mMessageCode;


   PDUMemberFunctions
};


class ForwardingLayerMessageStruct : public PDU {
public:
   ForwardingLayerMessageStruct();
   ForwardingHeaderStruct*       mHeader;
   std::vector<unsigned char>    mPayload;
   SignatureStruct*              mSig;


   PDUMemberFunctions
};


class ErrorResponseStruct : public PDU {
public:
   ErrorResponseStruct();
   UInt16                        mErrorCode;
   std::vector<unsigned char>    mReasonPhrase;
   std::vector<unsigned char>    mErrorInfo;


   PDUMemberFunctions
};


class JoinReqStruct : public PDU {
public:
   JoinReqStruct();
   NodeIdStruct*                 mJoiningPeerId;
   std::vector<unsigned char>    mOverlaySpecificData;


   PDUMemberFunctions
};


class JoinAnsStruct : public PDU {
public:
   JoinAnsStruct();
   std::vector<unsigned char>    mOverlaySpecificData;


   PDUMemberFunctions
};


class LeaveReqStruct : public PDU {
public:
   LeaveReqStruct();
   NodeIdStruct*                 mLeavingPeerId;
   std::vector<unsigned char>    mOverlaySpecificData;


   PDUMemberFunctions
};


class RouteQueryReqStruct : public PDU {
public:
   RouteQueryReqStruct();
   Boolean                       mSendUpdate;
   DestinationStruct*            mDestination;
   std::vector<unsigned char>    mOverlaySpecificData;


   PDUMemberFunctions
};


typedef enum {
   data = 128,
   ack = 129
} FramedMessageType;

class FramedMessageStruct : public PDU {
public:
   FramedMessageStruct();
   FramedMessageType             mType;
   struct {
        UInt32                        mSequence;
        std::vector<unsigned char>    mMessage;
   } mData;
   struct {
        UInt32                        mAckSequence;
        UInt32                        mReceived;
   } mAck;


   PDUMemberFunctions
};


class IceCandidateStruct : public PDU {
public:
   IceCandidateStruct();
   std::vector<unsigned char>    mCandidate;


   PDUMemberFunctions
};


class ConnectReqAnsStruct : public PDU {
public:
   ConnectReqAnsStruct();
   std::vector<unsigned char>    mUfrag;
   std::vector<unsigned char>    mPassword;
   UInt16                        mApplication;
   std::vector<unsigned char>    mRole;
   std::vector<IceCandidateStruct*>  mCandidates;


   PDUMemberFunctions
};


typedef enum {
   responsible_set = 1,
   num_resources = 2
} PingInformationType;

class PingReqStruct : public PDU {
public:
   PingReqStruct();
   std::vector<UInt8>            mRequestedInfo;


   PDUMemberFunctions
};


class PingInformationStruct : public PDU {
public:
   PingInformationStruct();
   PingInformationType           mType;
   struct {
        UInt32                        mResponsiblePpb;
   } mResponsibleSet;
   struct {
        UInt32                        mNumResources;
   } mNumResources;


   PDUMemberFunctions
};


class PingAnsStruct : public PDU {
public:
   PingAnsStruct();
   UInt64                        mResponseId;
   std::vector<PingInformationStruct*>  mPingInfo;


   PDUMemberFunctions
};


class TunnelReqStruct : public PDU {
public:
   TunnelReqStruct();
   UInt16                        mApplication;
   std::vector<unsigned char>    mDialogId;
   std::vector<unsigned char>    mApplicationPdu;


   PDUMemberFunctions
};


typedef enum {
   reserved_data_model = 0,
   single_value = 1,
   array = 2,
   dictionary = 3
} DataModel;

class DataValueStruct : public PDU {
public:
   DataValueStruct();
   Boolean                       mExists;
   std::vector<unsigned char>    mValue;


   PDUMemberFunctions
};


class ArrayEntryStruct : public PDU {
public:
   ArrayEntryStruct();
   UInt32                        mIndex;
   DataValueStruct*              mValue;


   PDUMemberFunctions
};


class DictionaryKeyStruct : public PDU {
public:
   DictionaryKeyStruct();
   std::vector<unsigned char>    mKey;


   PDUMemberFunctions
};


class DictionaryEntryStruct : public PDU {
public:
   DictionaryEntryStruct();
   DictionaryKeyStruct*          mKey;
   DataValueStruct*              mValue;


   PDUMemberFunctions
};


class StoredDataValueStruct : public PDU {
public:
   StoredDataValueStruct();
   DataModel                     mModel;
   struct {
        DataValueStruct*              mSingleValueEntry;
   } mSingleValue;
   struct {
        ArrayEntryStruct*             mArrayEntry;
   } mArray;
   struct {
        DictionaryEntryStruct*        mDictionaryEntry;
   } mDictionary;


   PDUMemberFunctions
};


class StoredDataStruct : public PDU {
public:
   StoredDataStruct();
   UInt32                        mLength;
   UInt64                        mStorageTime;
   UInt32                        mLifetime;
   StoredDataValueStruct*        mValue;
   SignatureStruct*              mSignature;


   PDUMemberFunctions
};


class StoreKindDataStruct : public PDU {
public:
   StoreKindDataStruct();
   UInt32                        mKind;
   DataModel                     mDataModel;
   UInt64                        mGenerationCounter;
   std::vector<StoredDataStruct*>  mValues;


   PDUMemberFunctions
};


class StoreReqStruct : public PDU {
public:
   StoreReqStruct();
   ResourceIdStruct*             mResource;
   UInt8                         mReplicaNumber;
   std::vector<StoreKindDataStruct*>  mKindData;


   PDUMemberFunctions
};


class StoreKindResponseStruct : public PDU {
public:
   StoreKindResponseStruct();
   UInt32                        mKind;
   UInt64                        mGenerationCounter;
   std::vector<NodeIdStruct*>    mReplicas;


   PDUMemberFunctions
};


class StoreAnsStruct : public PDU {
public:
   StoreAnsStruct();
   std::vector<StoreKindResponseStruct*>  mKindResponses;


   PDUMemberFunctions
};


class ArrayRangeStruct : public PDU {
public:
   ArrayRangeStruct();
   UInt32                        mFirst;
   UInt32                        mLast;


   PDUMemberFunctions
};


class StoredDataSpecifierStruct : public PDU {
public:
   StoredDataSpecifierStruct();
   UInt32                        mKind;
   DataModel                     mModel;
   UInt64                        mGeneration;
   UInt16                        mLength;
   struct {
   } mSingleValue;
   struct {
        std::vector<ArrayRangeStruct*>  mIndices;
   } mArray;
   struct {
        std::vector<DictionaryKeyStruct*>  mKeys;
   } mDictionary;


   PDUMemberFunctions
};


class FetchReqStruct : public PDU {
public:
   FetchReqStruct();
   ResourceIdStruct*             mResource;
   std::vector<StoredDataSpecifierStruct*>  mSpecifiers;


   PDUMemberFunctions
};


class FetchKindResponseStruct : public PDU {
public:
   FetchKindResponseStruct();
   UInt32                        mKind;
   UInt64                        mGeneration;
   std::vector<StoredDataStruct*>  mValues;


   PDUMemberFunctions
};


class FetchAnsStruct : public PDU {
public:
   FetchAnsStruct();
   std::vector<FetchKindResponseStruct*>  mKindResponses;


   PDUMemberFunctions
};


class RemoveReqStruct : public PDU {
public:
   RemoveReqStruct();
   ResourceIdStruct*             mResource;
   std::vector<StoredDataSpecifierStruct*>  mSpecifiers;


   PDUMemberFunctions
};


class RemoveAnsStruct : public PDU {
public:
   RemoveAnsStruct();
   std::vector<StoreKindResponseStruct*>  mKindResponses;


   PDUMemberFunctions
};


class FindReqStruct : public PDU {
public:
   FindReqStruct();
   ResourceIdStruct*             mResource;
   std::vector<UInt32>           mKinds;


   PDUMemberFunctions
};


class FindKindDataStruct : public PDU {
public:
   FindKindDataStruct();
   UInt32                        mKind;
   ResourceIdStruct*             mClosest;


   PDUMemberFunctions
};


class FindAnsStruct : public PDU {
public:
   FindAnsStruct();
   std::vector<FindKindDataStruct*>  mResults;


   PDUMemberFunctions
};


class TurnServerStruct : public PDU {
public:
   TurnServerStruct();
   UInt8                         mIteration;
   IpAddressAndPortStruct*       mServerAddress;


   PDUMemberFunctions
};


typedef enum {
   sip_registration_uri = 1,
   sip_registration_route = 2
} SipRegistrationType;

class SipRegistrationStruct : public PDU {
public:
   SipRegistrationStruct();
   SipRegistrationType           mType;
   UInt16                        mLength;
   struct {
        std::vector<unsigned char>    mUri;
   } mSipRegistrationUri;
   struct {
        std::vector<unsigned char>    mContactPrefs;
        std::vector<DestinationStruct*>  mDestinationList;
   } mSipRegistrationRoute;


   PDUMemberFunctions
};


typedef enum {
   reserved_chord = 0,
   peer_ready = 1,
   neighbors = 2,
   full = 3
} ChordUpdateType;

class ChordUpdateStruct : public PDU {
public:
   ChordUpdateStruct();
   ChordUpdateType               mType;
   struct {
   } mPeerReady;
   struct {
        std::vector<NodeIdStruct*>    mPredecessors;
        std::vector<NodeIdStruct*>    mSuccessors;
   } mNeighbors;
   struct {
        std::vector<NodeIdStruct*>    mPredecessors;
        std::vector<NodeIdStruct*>    mSuccessors;
        std::vector<NodeIdStruct*>    mFingers;
   } mFull;


   PDUMemberFunctions
};


class ChordRouteQueryAnsStruct : public PDU {
public:
   ChordRouteQueryAnsStruct();
   NodeIdStruct*                 mNextId;


   PDUMemberFunctions
};


}

#endif