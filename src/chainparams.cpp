// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The PIVX developers
// Copyright (c) 2017-2018 The Bitcoin Green developers
// Copyright (c) 2018-2019 The Cryptonodes developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"
#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of
    (0, uint256("0x0000008d5b81a80afddae66a5c211ad56ac03b031df0335449a19d4c7c30d436"))
    (50000, uint256("0x5049c6fdbf8ab79321583303eeeda0b94c23e7d0a997114bc28b6bcb503e4584"))
    (100000, uint256("0xb6fdb6eae051bc2b68dafc255d92e3cde82a90c83a2416cc3a816b791044e9eb"))
    (150000, uint256("0xc642a16c8fc84aea417c744fe3be197522bb220f8c2914f9eb4519bfa4842515"))
    (200000, uint256("1872d47d22b049cec00b3f6859c6e6cd20a804dc2d9936a48439b8c96948b60b"))
    (250000, uint256("d1b44dc74faf146ad816b9a9f655369e5e6c86a965c680e9c20540edc1335dd8"))
    (300000, uint256("4390cddd62b6bd588e8f0de57509e52bf8c99ad321d0b6fafa9ca249cb3202f5"))
    (350000, uint256("4165cd55872e403e3cdc7bb723e07cc709113739691c01f96411fab37bb73a4f"))
    (400000, uint256("c3577247ee5a7d6a9fb84067f154fe3c25335dcf0312e465b6bbcbc8b6c341db"))
    (450000, uint256("8e7eea9a29801c13e632b3eb0874aaf349a5ed1f710b487304a69b7816d7c0c1"))
    (455617, uint256("621db9d589d8df2e1ebf73187e76f7633ebe9d3da74dd6c1c26fae530808ebee"))
    (469796, uint256("0488a057efeea6cf9e8504a157eb37cacd26c48089de310982c7592bc7c96db8"));

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1558430519, // * UNIX timestamp of last checkpoint block
    1041423,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    3000        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of
    (0, uint256("0x001"));

static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1539698400,
    0,
    250};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of
    (0, uint256("0x001"));

static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1529411413,
    0,
    100};

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        pchMessageStart[0] = 0xcd;
        pchMessageStart[1] = 0x62;
        pchMessageStart[2] = 0xea;
        pchMessageStart[3] = 0x16;
        vAlertPubKey = ParseHex("0425977fe2a0518da9c9a4b4c1b8b881f5551615f0872e7e288b0220ab4c8b3e3d4e47a69aeed22ef689ccff22836fcac9722f908d7bf30a6541f4cf958a02abef");
        nDefaultPort = 44219;
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        nSubsidyHalvingInterval = 1050000;
        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 8100;
        nRejectBlockOutdatedMajority = 10260;
        nToCheckBlockUpgradeMajority = 10800;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // Cryptonodes: 1 day
        nTargetSpacing = 2 * 60;  // Cryptonodes: 2 minutes
        nMaturity = 10;
        nMasternodeCountDrift = 20;
        nMaxMoneyOut = 21000000 * COIN;

        /** Height or Time Based Activations **/
        nLastPOWBlock = 200;
        nModifierUpdateBlock = 1; // we use the version 2 for CNMC

        const char* pszTimestamp = "19.06.2018-13:13 It's time to have coins they not need a Powerplant. And together we can make Future Green! By Cab :-)";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 0 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("04807c15b493a2e5670206ac8a45fedbdbec44bc9541afb72f7114ea45579b93994c605288dc8a326785f42f7ae1c73ba1f0e7cdc674582b0bb4652a0e355b2972") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1529411413;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 2345584;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x0000008d5b81a80afddae66a5c211ad56ac03b031df0335449a19d4c7c30d436"));
        assert(genesis.hashMerkleRoot == uint256("0x4056baa34fc0c0afed7c76f24279cfcda5ac0b02a3efbf70175cc6b5232a4251"));

        // DNS Seeding
        vSeeds.push_back(CDNSSeedData("185.62.81.137", "185.62.81.137"));
        vSeeds.push_back(CDNSSeedData("185.62.81.136", "185.62.81.136"));
        vSeeds.push_back(CDNSSeedData("185.62.81.135", "185.62.81.135"));
        vSeeds.push_back(CDNSSeedData("185.62.81.134", "185.62.81.134"));
        vSeeds.push_back(CDNSSeedData("185.62.81.133", "185.62.81.133"));
        vSeeds.push_back(CDNSSeedData("185.62.81.132", "185.62.81.132"));
        vSeeds.push_back(CDNSSeedData("185.62.81.131", "185.62.81.131"));

        // Cryptonodes addresses start with 'c'
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 88);
        // Cryptonodes script addresses start with '7'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 16);
        // Cryptonodes private keys start with 'Z'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 81);
        // Cryptonodes BIP32 pubkeys start with 'xpub' (Bitcoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        // Cryptonodes BIP32 prvkeys start with 'xprv' (Bitcoin defaults)
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();
        // Cryptonodes BIP44 coin type is '203' (0x800000cb)
        // BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0xcb).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 3;
        strSporkKey = "04067873AFD8DED0794012043DE67BCB34021DA5959D48172C5C7D5EB466303D91A4436CDA7761B4BB668BEE3E6E2BAE4ABD2771296C739CA039693C9C00A7C4E8";
        strMasternodePoolDummyAddress = "cfAxpVxZGd2h6NWH68AMRXGQxbh19zPY52";
        nStartMasternodePayments = genesis.nTime + 86400; // 24 hours after genesis creation

        nBudget_Fee_Confirmations = 6; // Number of confirmations for the finalization fee
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};
static CMainParams mainParams;

class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0xac;
        pchMessageStart[1] = 0xed;
        pchMessageStart[2] = 0x2d;
        pchMessageStart[3] = 0x34;
        vAlertPubKey = ParseHex("044cc6ad807dcb4a0d3dfe342316279970a4f322dfb951580e60d0740299f20084a2628fd447f59152838cef082443772a2946d43e8ee492ca43f13b63bbdf54b1");
        nDefaultPort = 44220;
        nEnforceBlockUpgradeMajority = 8100;
        nRejectBlockOutdatedMajority = 10260;
        nToCheckBlockUpgradeMajority = 10800;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // Cryptonodes: 1 day
        nTargetSpacing = 2 * 60;  // Cryptonodes: 1 minute
        nLastPOWBlock = 200;
        nMaturity = 15;
        nMasternodeCountDrift = 4;
        nModifierUpdateBlock = 1;
        nMaxMoneyOut = 21000000 * COIN;

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1539698400;
        genesis.nNonce = 2879459;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x00000191f104a8075035f85872ec087330b722d66ff55c4820bd188d540d4741"));

        vFixedSeeds.clear();
        vSeeds.clear();

        // Testnet CNMC addresses start with 'g'
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 98);
        // Testnet CNMC script addresses start with '5' or '6'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 12);
        // Testnet private keys start with 'k'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 108);
        // Testnet CNMC BIP32 pubkeys start with 'tpub' (Bitcoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        // Testnet CNMC BIP32 prvkeys start with 'tprv' (Bitcoin defaults)
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();
        // Testnet CNMC BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        strSporkKey = "04DE2FDC95F5D532713BF870878B7775097CB124D5BA4213DF23EF1E52862BE33636E721EA89B13A6B5FB1D9B19132E10399DC6D6106013ED0C863E6560DD1439B";
        strMasternodePoolDummyAddress = "gYAkjyGZVnvJBEjHF1eyDRdnxoazvRxEtG";
        nStartMasternodePayments = genesis.nTime + 86400; // 24 hours after genesis
        nBudget_Fee_Confirmations = 3; // Number of confirmations for the finalization fee. We have to make this very short
                                       // here because we only have a 8 block finalization window on testnet
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        strNetworkID = "regtest";
        pchMessageStart[0] = 0xde;
        pchMessageStart[1] = 0x24;
        pchMessageStart[2] = 0xac;
        pchMessageStart[3] = 0x61;
	nDefaultPort = 44231;
        nSubsidyHalvingInterval = 150;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60; // Cryptonodes: 1 day
        nTargetSpacing = 2 * 60;        // Cryptonodes: 1 minutes
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1529411413;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 4;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x5e4b778aa1c49d60f0df414f9fcfc3aad23868268bca2211b5f5576adbc0a083"));

        vFixedSeeds.clear(); //! Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Regtest mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 44232;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval) { nSubsidyHalvingInterval = anSubsidyHalvingInterval; }
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority) { nEnforceBlockUpgradeMajority = anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority) { nRejectBlockOutdatedMajority = anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority) { nToCheckBlockUpgradeMajority = anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) { fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;


static CChainParams* pCurrentParams = 0;

CModifiableParams* ModifiableParams()
{
    assert(pCurrentParams);
    assert(pCurrentParams == &unitTestParams);
    return (CModifiableParams*)&unitTestParams;
}

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    case CBaseChainParams::UNITTEST:
        return unitTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
