<?xml version="1.0" encoding="UTF-8"?>
<drawing version="7">
    <attr value="kintex7" name="DeviceFamilyName">
        <trait delete="all:0" />
        <trait editname="all:0" />
        <trait edittrait="all:0" />
    </attr>
    <netlist>
        <signal name="HEX(3:0)" />
        <signal name="p" />
        <signal name="LE" />
        <signal name="Scan(1:0)" />
        <signal name="Hexs(15:0)" />
        <signal name="points(3:0)" />
        <signal name="points(3)" />
        <signal name="points(2)" />
        <signal name="points(1)" />
        <signal name="points(0)" />
        <signal name="LES(3:0)" />
        <signal name="LES(3)" />
        <signal name="LES(2)" />
        <signal name="LES(1)" />
        <signal name="LES(0)" />
        <signal name="Hexs(3:0)" />
        <signal name="Hexs(7:4)" />
        <signal name="Hexs(11:8)" />
        <signal name="Hexs(15:12)" />
        <signal name="V1" />
        <signal name="V0" />
        <signal name="Scan(1)" />
        <signal name="Scan(0)" />
        <signal name="XLXN_5" />
        <signal name="XLXN_6" />
        <signal name="XLXN_7" />
        <signal name="XLXN_8" />
        <signal name="XLXN_9" />
        <signal name="AN(3:0)" />
        <signal name="AN(3)" />
        <signal name="AN(2)" />
        <signal name="AN(1)" />
        <signal name="AN(0)" />
        <port polarity="Output" name="HEX(3:0)" />
        <port polarity="Output" name="p" />
        <port polarity="Output" name="LE" />
        <port polarity="Input" name="Scan(1:0)" />
        <port polarity="Input" name="Hexs(15:0)" />
        <port polarity="Input" name="points(3:0)" />
        <port polarity="Input" name="LES(3:0)" />
        <port polarity="Output" name="AN(3:0)" />
        <blockdef name="Mux4to1b4">
            <timestamp>2023-10-31T8:4:3</timestamp>
            <rect width="256" x="64" y="-320" height="320" />
            <rect width="64" x="0" y="-300" height="24" />
            <line x2="0" y1="-288" y2="-288" x1="64" />
            <rect width="64" x="0" y="-236" height="24" />
            <line x2="0" y1="-224" y2="-224" x1="64" />
            <rect width="64" x="0" y="-172" height="24" />
            <line x2="0" y1="-160" y2="-160" x1="64" />
            <rect width="64" x="0" y="-108" height="24" />
            <line x2="0" y1="-96" y2="-96" x1="64" />
            <rect width="64" x="0" y="-44" height="24" />
            <line x2="0" y1="-32" y2="-32" x1="64" />
            <rect width="64" x="320" y="-300" height="24" />
            <line x2="384" y1="-288" y2="-288" x1="320" />
        </blockdef>
        <blockdef name="Mux4to1">
            <timestamp>2023-11-17T15:15:34</timestamp>
            <rect width="256" x="64" y="-320" height="320" />
            <line x2="0" y1="-288" y2="-288" x1="64" />
            <line x2="0" y1="-224" y2="-224" x1="64" />
            <line x2="0" y1="-160" y2="-160" x1="64" />
            <line x2="0" y1="-96" y2="-96" x1="64" />
            <rect width="64" x="0" y="-44" height="24" />
            <line x2="0" y1="-32" y2="-32" x1="64" />
            <line x2="384" y1="-288" y2="-288" x1="320" />
        </blockdef>
        <blockdef name="vcc">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-32" y2="-64" x1="64" />
            <line x2="64" y1="0" y2="-32" x1="64" />
            <line x2="32" y1="-64" y2="-64" x1="96" />
        </blockdef>
        <blockdef name="gnd">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-64" y2="-96" x1="64" />
            <line x2="52" y1="-48" y2="-48" x1="76" />
            <line x2="60" y1="-32" y2="-32" x1="68" />
            <line x2="40" y1="-64" y2="-64" x1="88" />
            <line x2="64" y1="-64" y2="-80" x1="64" />
            <line x2="64" y1="-128" y2="-96" x1="64" />
        </blockdef>
        <blockdef name="d2_4e">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <rect width="256" x="64" y="-384" height="320" />
            <line x2="64" y1="-128" y2="-128" x1="0" />
            <line x2="64" y1="-256" y2="-256" x1="0" />
            <line x2="64" y1="-320" y2="-320" x1="0" />
            <line x2="320" y1="-128" y2="-128" x1="384" />
            <line x2="320" y1="-192" y2="-192" x1="384" />
            <line x2="320" y1="-256" y2="-256" x1="384" />
            <line x2="320" y1="-320" y2="-320" x1="384" />
        </blockdef>
        <blockdef name="inv">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-32" y2="-32" x1="0" />
            <line x2="160" y1="-32" y2="-32" x1="224" />
            <line x2="128" y1="-64" y2="-32" x1="64" />
            <line x2="64" y1="-32" y2="0" x1="128" />
            <line x2="64" y1="0" y2="-64" x1="64" />
            <circle r="16" cx="144" cy="-32" />
        </blockdef>
        <block symbolname="Mux4to1b4" name="XLXI_1">
            <blockpin signalname="Scan(1:0)" name="S(1:0)" />
            <blockpin signalname="Hexs(7:4)" name="I1(3:0)" />
            <blockpin signalname="Hexs(15:12)" name="I3(3:0)" />
            <blockpin signalname="Hexs(3:0)" name="I0(3:0)" />
            <blockpin signalname="Hexs(11:8)" name="I2(3:0)" />
            <blockpin signalname="HEX(3:0)" name="O(3:0)" />
        </block>
        <block symbolname="Mux4to1" name="XLXI_2">
            <blockpin signalname="Scan(1:0)" name="S(1:0)" />
            <blockpin signalname="points(0)" name="I0" />
            <blockpin signalname="points(1)" name="I1" />
            <blockpin signalname="points(2)" name="I2" />
            <blockpin signalname="points(3)" name="I3" />
            <blockpin signalname="p" name="O" />
        </block>
        <block symbolname="Mux4to1" name="XLXI_3">
            <blockpin signalname="Scan(1:0)" name="S(1:0)" />
            <blockpin signalname="LES(0)" name="I0" />
            <blockpin signalname="LES(1)" name="I1" />
            <blockpin signalname="LES(2)" name="I2" />
            <blockpin signalname="LES(3)" name="I3" />
            <blockpin signalname="LE" name="O" />
        </block>
        <block symbolname="vcc" name="XLXI_9">
            <blockpin signalname="V1" name="P" />
        </block>
        <block symbolname="gnd" name="XLXI_10">
            <blockpin signalname="V0" name="G" />
        </block>
        <block symbolname="d2_4e" name="XLXI_11">
            <blockpin signalname="Scan(0)" name="A0" />
            <blockpin signalname="Scan(1)" name="A1" />
            <blockpin signalname="XLXN_5" name="E" />
            <blockpin signalname="XLXN_6" name="D0" />
            <blockpin signalname="XLXN_7" name="D1" />
            <blockpin signalname="XLXN_8" name="D2" />
            <blockpin signalname="XLXN_9" name="D3" />
        </block>
        <block symbolname="vcc" name="XLXI_12">
            <blockpin signalname="XLXN_5" name="P" />
        </block>
        <block symbolname="inv" name="XLXI_13">
            <blockpin signalname="XLXN_6" name="I" />
            <blockpin signalname="AN(0)" name="O" />
        </block>
        <block symbolname="inv" name="XLXI_14">
            <blockpin signalname="XLXN_7" name="I" />
            <blockpin signalname="AN(1)" name="O" />
        </block>
        <block symbolname="inv" name="XLXI_15">
            <blockpin signalname="XLXN_8" name="I" />
            <blockpin signalname="AN(2)" name="O" />
        </block>
        <block symbolname="inv" name="XLXI_16">
            <blockpin signalname="XLXN_9" name="I" />
            <blockpin signalname="AN(3)" name="O" />
        </block>
    </netlist>
    <sheet sheetnum="1" width="3520" height="2720">
        <instance x="784" y="672" name="XLXI_1" orien="R0">
        </instance>
        <instance x="784" y="1168" name="XLXI_2" orien="R0">
        </instance>
        <instance x="768" y="1648" name="XLXI_3" orien="R0">
        </instance>
        <branch name="HEX(3:0)">
            <wire x2="1616" y1="384" y2="384" x1="1168" />
        </branch>
        <iomarker fontsize="28" x="1616" y="384" name="HEX(3:0)" orien="R0" />
        <branch name="p">
            <wire x2="1616" y1="880" y2="880" x1="1168" />
        </branch>
        <iomarker fontsize="28" x="1616" y="880" name="p" orien="R0" />
        <branch name="LE">
            <wire x2="1168" y1="1360" y2="1360" x1="1152" />
            <wire x2="1168" y1="1360" y2="1376" x1="1168" />
            <wire x2="1600" y1="1376" y2="1376" x1="1168" />
        </branch>
        <iomarker fontsize="28" x="1600" y="1376" name="LE" orien="R0" />
        <branch name="Scan(1:0)">
            <wire x2="416" y1="320" y2="320" x1="208" />
            <wire x2="416" y1="320" y2="384" x1="416" />
            <wire x2="784" y1="384" y2="384" x1="416" />
            <wire x2="416" y1="384" y2="448" x1="416" />
            <wire x2="416" y1="448" y2="1136" x1="416" />
            <wire x2="784" y1="1136" y2="1136" x1="416" />
            <wire x2="416" y1="1136" y2="1616" x1="416" />
            <wire x2="768" y1="1616" y2="1616" x1="416" />
            <wire x2="416" y1="1616" y2="1904" x1="416" />
            <wire x2="416" y1="1904" y2="1936" x1="416" />
            <wire x2="416" y1="1936" y2="2000" x1="416" />
            <wire x2="416" y1="2000" y2="2304" x1="416" />
            <wire x2="432" y1="1904" y2="1904" x1="416" />
        </branch>
        <iomarker fontsize="28" x="208" y="320" name="Scan(1:0)" orien="R180" />
        <iomarker fontsize="28" x="112" y="576" name="Hexs(15:0)" orien="R180" />
        <branch name="Hexs(15:0)">
            <wire x2="192" y1="576" y2="576" x1="112" />
            <wire x2="192" y1="576" y2="640" x1="192" />
            <wire x2="192" y1="640" y2="736" x1="192" />
            <wire x2="192" y1="400" y2="448" x1="192" />
            <wire x2="192" y1="448" y2="464" x1="192" />
            <wire x2="224" y1="464" y2="464" x1="192" />
            <wire x2="192" y1="464" y2="512" x1="192" />
            <wire x2="192" y1="512" y2="576" x1="192" />
        </branch>
        <branch name="points(3:0)">
            <wire x2="256" y1="832" y2="832" x1="32" />
            <wire x2="256" y1="832" y2="880" x1="256" />
            <wire x2="256" y1="880" y2="944" x1="256" />
            <wire x2="256" y1="944" y2="1008" x1="256" />
            <wire x2="256" y1="1008" y2="1072" x1="256" />
            <wire x2="256" y1="1072" y2="1152" x1="256" />
        </branch>
        <iomarker fontsize="28" x="32" y="832" name="points(3:0)" orien="R180" />
        <bustap x2="352" y1="1072" y2="1072" x1="256" />
        <branch name="points(3)">
            <attrtext style="alignment:SOFT-LEFT;fontsize:28;fontname:Arial" attrname="Name" x="568" y="1072" type="branch" />
            <wire x2="576" y1="1072" y2="1072" x1="352" />
            <wire x2="784" y1="1072" y2="1072" x1="576" />
        </branch>
        <bustap x2="352" y1="1008" y2="1008" x1="256" />
        <branch name="points(2)">
            <attrtext style="alignment:SOFT-LEFT;fontsize:28;fontname:Arial" attrname="Name" x="568" y="1008" type="branch" />
            <wire x2="576" y1="1008" y2="1008" x1="352" />
            <wire x2="784" y1="1008" y2="1008" x1="576" />
        </branch>
        <bustap x2="352" y1="944" y2="944" x1="256" />
        <branch name="points(1)">
            <attrtext style="alignment:SOFT-LEFT;fontsize:28;fontname:Arial" attrname="Name" x="568" y="944" type="branch" />
            <wire x2="576" y1="944" y2="944" x1="352" />
            <wire x2="784" y1="944" y2="944" x1="576" />
        </branch>
        <bustap x2="352" y1="880" y2="880" x1="256" />
        <branch name="points(0)">
            <attrtext style="alignment:SOFT-LEFT;fontsize:28;fontname:Arial" attrname="Name" x="568" y="880" type="branch" />
            <wire x2="576" y1="880" y2="880" x1="352" />
            <wire x2="784" y1="880" y2="880" x1="576" />
        </branch>
        <branch name="LES(3:0)">
            <wire x2="240" y1="1264" y2="1264" x1="176" />
            <wire x2="240" y1="1264" y2="1344" x1="240" />
            <wire x2="240" y1="1344" y2="1360" x1="240" />
            <wire x2="240" y1="1360" y2="1424" x1="240" />
            <wire x2="240" y1="1424" y2="1488" x1="240" />
            <wire x2="240" y1="1488" y2="1552" x1="240" />
            <wire x2="240" y1="1552" y2="1584" x1="240" />
            <wire x2="240" y1="1584" y2="1584" x1="224" />
        </branch>
        <bustap x2="336" y1="1552" y2="1552" x1="240" />
        <branch name="LES(3)">
            <attrtext style="alignment:SOFT-LEFT;fontsize:28;fontname:Arial" attrname="Name" x="552" y="1552" type="branch" />
            <wire x2="560" y1="1552" y2="1552" x1="336" />
            <wire x2="768" y1="1552" y2="1552" x1="560" />
        </branch>
        <bustap x2="336" y1="1488" y2="1488" x1="240" />
        <branch name="LES(2)">
            <attrtext style="alignment:SOFT-LEFT;fontsize:28;fontname:Arial" attrname="Name" x="552" y="1488" type="branch" />
            <wire x2="560" y1="1488" y2="1488" x1="336" />
            <wire x2="768" y1="1488" y2="1488" x1="560" />
        </branch>
        <bustap x2="336" y1="1424" y2="1424" x1="240" />
        <branch name="LES(1)">
            <attrtext style="alignment:SOFT-LEFT;fontsize:28;fontname:Arial" attrname="Name" x="552" y="1424" type="branch" />
            <wire x2="560" y1="1424" y2="1424" x1="336" />
            <wire x2="768" y1="1424" y2="1424" x1="560" />
        </branch>
        <bustap x2="336" y1="1360" y2="1360" x1="240" />
        <branch name="LES(0)">
            <attrtext style="alignment:SOFT-LEFT;fontsize:28;fontname:Arial" attrname="Name" x="552" y="1360" type="branch" />
            <wire x2="560" y1="1360" y2="1360" x1="336" />
            <wire x2="768" y1="1360" y2="1360" x1="560" />
        </branch>
        <bustap x2="288" y1="576" y2="576" x1="192" />
        <branch name="Hexs(3:0)">
            <attrtext style="alignment:SOFT-LEFT;fontsize:28;fontname:Arial" attrname="Name" x="536" y="576" type="branch" />
            <wire x2="544" y1="576" y2="576" x1="288" />
            <wire x2="784" y1="576" y2="576" x1="544" />
        </branch>
        <bustap x2="288" y1="448" y2="448" x1="192" />
        <branch name="Hexs(7:4)">
            <attrtext style="alignment:SOFT-LEFT;fontsize:28;fontname:Arial" attrname="Name" x="536" y="448" type="branch" />
            <wire x2="544" y1="448" y2="448" x1="288" />
            <wire x2="784" y1="448" y2="448" x1="544" />
        </branch>
        <bustap x2="288" y1="640" y2="640" x1="192" />
        <branch name="Hexs(11:8)">
            <attrtext style="alignment:SOFT-LEFT;fontsize:28;fontname:Arial" attrname="Name" x="536" y="640" type="branch" />
            <wire x2="544" y1="640" y2="640" x1="288" />
            <wire x2="784" y1="640" y2="640" x1="544" />
        </branch>
        <bustap x2="288" y1="512" y2="512" x1="192" />
        <branch name="Hexs(15:12)">
            <attrtext style="alignment:SOFT-LEFT;fontsize:28;fontname:Arial" attrname="Name" x="536" y="512" type="branch" />
            <wire x2="544" y1="512" y2="512" x1="288" />
            <wire x2="784" y1="512" y2="512" x1="544" />
        </branch>
        <instance x="48" y="1888" name="XLXI_9" orien="R0" />
        <instance x="48" y="2224" name="XLXI_10" orien="R0" />
        <branch name="V1">
            <attrtext style="alignment:SOFT-VRIGHT;fontsize:28;fontname:Arial" attrname="Name" x="112" y="1936" type="branch" />
            <wire x2="112" y1="1888" y2="1936" x1="112" />
        </branch>
        <branch name="V0">
            <attrtext style="alignment:SOFT-VLEFT;fontsize:28;fontname:Arial" attrname="Name" x="112" y="2048" type="branch" />
            <wire x2="112" y1="2048" y2="2096" x1="112" />
        </branch>
        <iomarker fontsize="28" x="176" y="1264" name="LES(3:0)" orien="R180" />
        <instance x="880" y="2256" name="XLXI_11" orien="R0" />
        <bustap x2="512" y1="2000" y2="2000" x1="416" />
        <branch name="Scan(1)">
            <attrtext style="alignment:SOFT-BCENTER;fontsize:28;fontname:Arial" attrname="Name" x="696" y="2000" type="branch" />
            <wire x2="696" y1="2000" y2="2000" x1="512" />
            <wire x2="880" y1="2000" y2="2000" x1="696" />
        </branch>
        <bustap x2="512" y1="1936" y2="1936" x1="416" />
        <branch name="Scan(0)">
            <attrtext style="alignment:SOFT-BCENTER;fontsize:28;fontname:Arial" attrname="Name" x="696" y="1936" type="branch" />
            <wire x2="696" y1="1936" y2="1936" x1="512" />
            <wire x2="880" y1="1936" y2="1936" x1="696" />
        </branch>
        <instance x="688" y="2144" name="XLXI_12" orien="R180" />
        <branch name="XLXN_5">
            <wire x2="880" y1="2128" y2="2128" x1="624" />
            <wire x2="624" y1="2128" y2="2144" x1="624" />
        </branch>
        <branch name="XLXN_6">
            <wire x2="1296" y1="1936" y2="1936" x1="1264" />
        </branch>
        <instance x="1296" y="1968" name="XLXI_13" orien="R0" />
        <branch name="XLXN_7">
            <wire x2="1296" y1="2000" y2="2000" x1="1264" />
        </branch>
        <instance x="1296" y="2032" name="XLXI_14" orien="R0" />
        <branch name="XLXN_8">
            <wire x2="1296" y1="2064" y2="2064" x1="1264" />
        </branch>
        <instance x="1296" y="2096" name="XLXI_15" orien="R0" />
        <branch name="XLXN_9">
            <wire x2="1296" y1="2128" y2="2128" x1="1264" />
        </branch>
        <instance x="1296" y="2160" name="XLXI_16" orien="R0" />
        <branch name="AN(3:0)">
            <wire x2="1664" y1="1904" y2="1936" x1="1664" />
            <wire x2="1664" y1="1936" y2="2000" x1="1664" />
            <wire x2="1664" y1="2000" y2="2064" x1="1664" />
            <wire x2="1664" y1="2064" y2="2128" x1="1664" />
            <wire x2="1664" y1="2128" y2="2224" x1="1664" />
        </branch>
        <iomarker fontsize="28" x="1664" y="2224" name="AN(3:0)" orien="R90" />
        <bustap x2="1568" y1="2128" y2="2128" x1="1664" />
        <branch name="AN(3)">
            <attrtext style="alignment:SOFT-BCENTER;fontsize:28;fontname:Arial" attrname="Name" x="1544" y="2128" type="branch" />
            <wire x2="1544" y1="2128" y2="2128" x1="1520" />
            <wire x2="1568" y1="2128" y2="2128" x1="1544" />
        </branch>
        <bustap x2="1568" y1="2064" y2="2064" x1="1664" />
        <branch name="AN(2)">
            <attrtext style="alignment:SOFT-BCENTER;fontsize:28;fontname:Arial" attrname="Name" x="1544" y="2064" type="branch" />
            <wire x2="1544" y1="2064" y2="2064" x1="1520" />
            <wire x2="1568" y1="2064" y2="2064" x1="1544" />
        </branch>
        <bustap x2="1568" y1="2000" y2="2000" x1="1664" />
        <branch name="AN(1)">
            <attrtext style="alignment:SOFT-BCENTER;fontsize:28;fontname:Arial" attrname="Name" x="1544" y="2000" type="branch" />
            <wire x2="1544" y1="2000" y2="2000" x1="1520" />
            <wire x2="1568" y1="2000" y2="2000" x1="1544" />
        </branch>
        <bustap x2="1568" y1="1936" y2="1936" x1="1664" />
        <branch name="AN(0)">
            <attrtext style="alignment:SOFT-BCENTER;fontsize:28;fontname:Arial" attrname="Name" x="1544" y="1936" type="branch" />
            <wire x2="1544" y1="1936" y2="1936" x1="1520" />
            <wire x2="1568" y1="1936" y2="1936" x1="1544" />
        </branch>
    </sheet>
</drawing>