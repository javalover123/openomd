#include <gtest/gtest.h>
#include "omdc_sbe/AggregateOrderBookUpdate.h"
#include "omdc_sbe/SecurityStatus.h"
#include "omdc_sbe/SequenceReset.h"
#include "omdc_sbe/Logon.h"
#include "openomd/omdcparser.h"

namespace omdc
{
namespace sbe
{
class OMDCProcessor
{
#define ONMESSAGE(_MSG) virtual void onMessage(_MSG const&, int32_t){}

public:
    ONMESSAGE(AddOddLotOrder)
    ONMESSAGE(AddOrder)
    ONMESSAGE(AggregateOrderBookUpdate)
    ONMESSAGE(BrokerQueue)
    ONMESSAGE(ClosingPrice)
    ONMESSAGE(CurrencyRate)
    ONMESSAGE(DeleteOddLotOrder)
    ONMESSAGE(DeleteOrder)
    ONMESSAGE(DisasterRecoverySignal)
    ONMESSAGE(IndexData)
    ONMESSAGE(IndexDefinition)
    ONMESSAGE(IndicativeEquilibriumPrice)
    ONMESSAGE(LiquidityProvider)
    ONMESSAGE(Logon)
    ONMESSAGE(LogonResponse)
    ONMESSAGE(MarketDefinition)
    ONMESSAGE(ModifyOrder)
    ONMESSAGE(NominalPrice)
    ONMESSAGE(OrderImbalance)
    ONMESSAGE(ReferencePrice)
    ONMESSAGE(RefreshComplete)
    ONMESSAGE(RetransmissionReq)
    ONMESSAGE(RetransmissionResp)
    ONMESSAGE(SecurityDefinition)
    ONMESSAGE(SecurityStatus)
    ONMESSAGE(SequenceReset)
    ONMESSAGE(Trade)
    ONMESSAGE(TradeCancel)
    ONMESSAGE(TradeTicker)
    ONMESSAGE(TradingSessionStatus)
    ONMESSAGE(VCMTrigger)
    void onUnknownMessage(uint16_t, uint16_t)
    {
    }
};

template <typename _Processor>
void processMsg(char* msg, size_t size)
{
    _Processor processor;
    openomd::OmdcParser parser;
    parser.parse(msg, size, processor, 0);
}

TEST(OMDC_TEST, SequenceReset)
{
    char msg[] = "\x18\x00\x01\x02\x01\x00\x00\x00\x80\x73\x01\x12\xc8\xf4\x12\x15" \
        "\x08\x00\x64\x00\x01\x00\x00\x00";
    struct Processor : public OMDCProcessor
    {
        void onMessage(sbe::SequenceReset const& sr, int32_t partition)
        {
            EXPECT_EQ(1, sr.newSeqNo());
        }
        using OMDCProcessor::onMessage;
    };
    processMsg<Processor>(msg, sizeof(msg) - 1);
}

TEST(OMDC_TEST, Logon)
{
}

TEST(OMDC_TEST, LogonResponse)
{
}

TEST(OMDC_TEST, DisasterRecoverySignal)
{

}

TEST(OMDC_TEST, RetransmissionRequest)
{

}

TEST(OMDC_TEST, RetransmissionResponse)
{

}

TEST(OMDC_TEST, RefreshComplete)
{
    char msg[] = "\x18\x00\x01\x5d\x01\x00\x00\x00\x40\x87\x44\xa5\xa2\x10\x45\x15" \
        "\x08\x00\xcb\x00\x00\x00\x00\x00";
    struct Processor : public OMDCProcessor
    {
        void onMessage(sbe::RefreshComplete const& rc, int32_t partition)
        {
            EXPECT_EQ(0, rc.lastSeqNum());
        }
        using OMDCProcessor::onMessage;
    };
    processMsg<Processor>(msg, sizeof(msg) - 1);
}

TEST(OMDC_TEST, MarketDefinition)
{

}

TEST(OMDC_TEST, SecurityDefinition)
{
    char msg[] = "\x98\x05\x03\x02\x82\x0d\x00\x00\x00\xc8\xb9\xc1\x08\xf5\x12\x15" \
        "\xd8\x01\x0b\x00\x8f\x2c\x00\x00\x4d\x41\x49\x4e\x4e\x4c\x30\x30" \
        "\x31\x32\x34\x38\x34\x35\x31\x33\x57\x52\x4e\x54\x03\x00\x30\x31" \
        "\x42\x50\x2d\x49\x43\x42\x43\x40\x45\x43\x31\x38\x31\x30\x42\x20" \
        "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20" \
        "\x20\x20\x20\x20\x20\x20\x20\x20\x48\x4b\x44\xe5\x5d\x4c\x88\xd5" \
        "\x6c\xf4\x5d\x6b\x51\x41\x53\xfc\x8c\x22\xff\x00\x30\x00\x30\x00" \
        "\x30\x00\x30\x00\x30\x00\x30\x00\x30\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\xe5\x5d\x4c\x88\xd5\x6c\xf4\x5d\x6b" \
        "\x51\x41\x53\x2d\x8d\x22\xff\x00\x30\x00\x30\x00\x30\x00\x30\x00" \
        "\x30\x00\x30\x00\x30\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00\x00\xe8\x03\x00\x00\x00\x00\x00\x00\x44\x02\x00\x00\x4e" \
        "\x4e\x4e\x59\x4e\x4e\x4e\x00\x4d\xc8\x33\x01\x00\x00\x00\x00\x45" \
        "\x58\x45\x52\x20\x44\x41\x54\x45\x3a\x30\x33\x2f\x31\x30\x2f\x31" \
        "\x38\x20\x2a\x4c\x50\x39\x36\x39\x32\x2d\x32\x31\x30\x38\x20\x35" \
        "\x36\x30\x30\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20" \
        "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20" \
        "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20" \
        "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20" \
        "\x20\x20\x20\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x20\x20\x20\x00\x00\x00\x00\x20\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\x64\x19" \
        "\x00\x00\x00\x00\x00\x00\x0b\xf0\x33\x01\x43\x45\x00\x00\x4e\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x00\x03\x00\x00\x00\x00\x20\x20\x20" \
        "\x20\x20\x20\x20\x20\x20\x20\x20\x00\x00\x00\x00\x00\x00\x00\x00" \
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00" \
        "\x76\x05\x00\x00\xe8\x03\x00\x00";

    struct Processor : public OMDCProcessor
    {
        void onMessage(sbe::SecurityDefinition& sd, int32_t)
        {
            EXPECT_EQ(11407, sd.securityCode());
            EXPECT_EQ("MAIN", sd.getMarketCodeAsString());
            EXPECT_EQ("NL0012484513", sd.getIsinCodeAsString());
            EXPECT_EQ("WRNT", sd.getInstrumentTypeAsString());
            EXPECT_EQ(3, sd.productType());
            EXPECT_EQ("01", sd.getSpreadTableCodeAsString());
            EXPECT_EQ("BP-ICBC@EC1810B                         ", sd.getSecurityShortNameAsString());
            EXPECT_EQ("HKD", sd.getCurrencyCodeAsString());
            EXPECT_EQ(1000, sd.lotSize());
            EXPECT_EQ(580, sd.previousClosingPrice());
            EXPECT_EQ(78, sd.vcmFlag());
            EXPECT_EQ(78, sd.shortSellFlag());
            EXPECT_EQ(78, sd.casFlag());
            EXPECT_EQ(89, sd.ccassFlag());
            EXPECT_EQ(78, sd.dummySecurityFlag());
            EXPECT_EQ(78, sd.stampDutyFlag());
            EXPECT_EQ(20170829, sd.listingDate());
            EXPECT_EQ(0, sd.delistingDate());
            EXPECT_EQ("EXER DATE:03/10/18 *LP9692-2108 5600  ", sd.getFreeTextAsString());
            EXPECT_EQ(0, sd.efnFlag());
            EXPECT_EQ(0, sd.accruedInterest());
            EXPECT_EQ(0, sd.couponRate());
            EXPECT_EQ(1000, sd.conversionRatio());
            EXPECT_EQ(6500, sd.strikePrice1());
            EXPECT_EQ(0, sd.strikePrice2());
            EXPECT_EQ(20181003, sd.maturityDate());
            EXPECT_EQ(67, sd.callPutFlag());
            EXPECT_EQ(69, sd.style());
            EXPECT_EQ(78, sd.warrantType());
            EXPECT_EQ(0, sd.callPrice());
            EXPECT_EQ(0, sd.decimalsInCallPrice());
            EXPECT_EQ(0, sd.entitlement());
            EXPECT_EQ(3, sd.decimalsInEntitlement());
            EXPECT_EQ(0, sd.noWarrantsPerEntitlement());
            auto& underlyings = sd.noUnderlyingSecurities();
            EXPECT_EQ(1, underlyings.count());
            EXPECT_EQ(true, underlyings.hasNext());
            auto& u1 = underlyings.next();
            EXPECT_EQ(1398, u1.underlyingSecurityCode());
        }
        using OMDCProcessor::onMessage;
    };
    processMsg<Processor>(msg, sizeof(msg) - 1);
}

TEST(OMDC_TEST, LiquidityProvider)
{

}

TEST(OMDC_TEST, CurrencyRate)
{

}

TEST(OMDC_TEST, TradingSessionStatus)
{
    char msg[] = "\x70\x00\x03\x02\x03\x00\x00\x00\x00\x91\x63\x8d\x06\xf5\x12\x15" \
        "\x20\x00\x14\x00\x47\x45\x4d\x20\x01\x64\x00\x30\x20\x20\x20\x20" \
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00";

    struct Processor : public OMDCProcessor
    {
        void onMessage(sbe::TradingSessionStatus const& ts, int32_t partition)
        {
            EXPECT_EQ("GEM ", ts.getMarketCodeAsString());
            EXPECT_EQ(100, ts.tradingSessionSubID());
            EXPECT_EQ(0, ts.tradingSesStatus());
            EXPECT_EQ(48, ts.tradingSesControlFlag());
            EXPECT_EQ(0, ts.startDateTime());
            EXPECT_EQ(0, ts.endDateTime());
        }
        using OMDCProcessor::onMessage;
    };
    processMsg<Processor>(msg, sizeof(msg) - 1);
}

TEST(OMDC_TEST, SecurityStatus)
{
    char msg[] = "\x30\x01\x18\xdd\x31\x00\x00\x00\x00\x99\x00\x43\x06\xf5\x12\x15" \
        "\x0c\x00\x15\x00\x46\x62\x00\x00\x02\x00\x00\x00";

    struct Processor : public OMDCProcessor
    {
        void onMessage(sbe::SecurityStatus const& ss, int32_t partition)
        {
            EXPECT_EQ(25158, ss.securityCode());
            EXPECT_EQ(2, ss.suspensionIndicator());
        }
        using OMDCProcessor::onMessage;
    };
    processMsg<Processor>(msg, sizeof(msg) - 1);
}

TEST(OMDC_TEST, AddOrder)
{

}

TEST(OMDC_TEST, ModifyOrder)
{

}

TEST(OMDC_TEST, DeleteOrder)
{

}

TEST(OMDC_TEST, AddOddLotOrder)
{

}

TEST(OMDC_TEST, DeleteOddLotOrder)
{

}

TEST(OMDC_TEST, AggregateOrderBookUpdate)
{
    
}

TEST(OMDC_TEST, BrokerQueue)
{
    
}


TEST(OMDC_TEST, OrderImbalance)
{

}

TEST(OMDC_TEST, Trade)
{

}

TEST(OMDC_TEST, TradeCancel)
{

}

TEST(OMDC_TEST, TradeTicker)
{

}

TEST(OMDC_TEST, ClosingPrice)
{
    
}

TEST(OMDC_TEST, NominalPrice)
{

}

TEST(OMDC_TEST, IndicativeEquilibriumPrice)
{

}

TEST(OMDC_TEST, ReferencePrice)
{

}

TEST(OMDC_TEST, VCMTrigger)
{

}

TEST(OMDC_TEST, Statistics)
{

}

TEST(OMDC_TEST, MarketTurnover)
{

}

TEST(OMDC_TEST, Yield)
{

}

TEST(OMDC_TEST, News)
{

}

TEST(OMDC_TEST, IndexDefinition)
{
    char msg[] = "\x24\x00\x01\x00\x01\x00\x00\x00\xc0\xb8\x9f\xd5\x03\xf5\x12\x15" \
        "\x14\x00\x46\x00\x30\x30\x30\x30\x30\x31\x20\x20\x20\x20\x20\x43" \
        "\x43\x4e\x59\x20";
    struct Processor : public OMDCProcessor
    {
        void onMessage(sbe::IndexDefinition const& id, int32_t partition)
        {
            EXPECT_EQ("000001     ", id.getIndexCodeAsString());
            EXPECT_EQ(67, id.indexSource());
            EXPECT_EQ("CNY", id.getCurrencyCodeAsString());
        }
        using OMDCProcessor::onMessage;
    };
    processMsg<Processor>(msg, sizeof(msg) - 1);
}

TEST(OMDC_TEST, IndexData)
{

}

}
}