<?xml version="1.0" encoding="UTF-8"?>
<drawing version="7">
    <attr value="artix7" name="DeviceFamilyName">
        <trait delete="all:0" />
        <trait editname="all:0" />
        <trait edittrait="all:0" />
    </attr>
    <netlist>
        <signal name="clk" />
        <signal name="rst" />
        <signal name="clkdiv(31:0)" />
        <signal name="HEXS(15:0)" />
        <signal name="points(3:0)" />
        <signal name="LES(3:0)" />
        <signal name="XLXN_8" />
        <signal name="XLXN_9" />
        <signal name="AN(3:0)" />
        <signal name="XLXN_11(3:0)" />
        <signal name="XLXN_11(3)" />
        <signal name="XLXN_11(2)" />
        <signal name="XLXN_11(1)" />
        <signal name="XLXN_11(0)" />
        <signal name="SEGMENT(7:0)" />
        <signal name="SEGMENT(7)" />
        <signal name="SEGMENT(6)" />
        <signal name="SEGMENT(5)" />
        <signal name="SEGMENT(4)" />
        <signal name="SEGMENT(2)" />
        <signal name="SEGMENT(1)" />
        <signal name="SEGMENT(0)" />
        <signal name="SEGMENT(3)" />
        <signal name="clkdiv(18:17)" />
        <port polarity="Input" name="clk" />
        <port polarity="Input" name="rst" />
        <port polarity="Input" name="HEXS(15:0)" />
        <port polarity="Input" name="points(3:0)" />
        <port polarity="Input" name="LES(3:0)" />
        <port polarity="Output" name="AN(3:0)" />
        <port polarity="Output" name="SEGMENT(7:0)" />
        <blockdef name="DisplaySync">
            <timestamp>2023-11-17T15:16:9</timestamp>
            <rect width="256" x="64" y="-256" height="256" />
            <rect width="64" x="0" y="-236" height="24" />
            <line x2="0" y1="-224" y2="-224" x1="64" />
            <rect width="64" x="0" y="-172" height="24" />
            <line x2="0" y1="-160" y2="-160" x1="64" />
            <rect width="64" x="0" y="-108" height="24" />
            <line x2="0" y1="-96" y2="-96" x1="64" />
            <rect width="64" x="0" y="-44" height="24" />
            <line x2="0" y1="-32" y2="-32" x1="64" />
            <rect width="64" x="320" y="-236" height="24" />
            <line x2="384" y1="-224" y2="-224" x1="320" />
            <line x2="384" y1="-160" y2="-160" x1="320" />
            <line x2="384" y1="-96" y2="-96" x1="320" />
            <rect width="64" x="320" y="-44" height="24" />
            <line x2="384" y1="-32" y2="-32" x1="320" />
        </blockdef>
        <blockdef name="clkdiv">
            <timestamp>2023-10-31T8:36:10</timestamp>
            <rect width="256" x="64" y="-128" height="128" />
            <line x2="0" y1="-96" y2="-96" x1="64" />
            <line x2="0" y1="-32" y2="-32" x1="64" />
            <rect width="64" x="320" y="-108" height="24" />
            <line x2="384" y1="-96" y2="-96" x1="320" />
        </blockdef>
        <blockdef name="MyMC14459">
            <timestamp>2023-10-31T5:6:40</timestamp>
            <rect width="256" x="64" y="-512" height="512" />
            <line x2="0" y1="-480" y2="-480" x1="64" />
            <line x2="0" y1="-400" y2="-400" x1="64" />
            <line x2="0" y1="-320" y2="-320" x1="64" />
            <line x2="0" y1="-240" y2="-240" x1="64" />
            <line x2="0" y1="-160" y2="-160" x1="64" />
            <line x2="0" y1="-80" y2="-80" x1="64" />
            <line x2="384" y1="-480" y2="-480" x1="320" />
            <line x2="384" y1="-416" y2="-416" x1="320" />
            <line x2="384" y1="-352" y2="-352" x1="320" />
            <line x2="384" y1="-288" y2="-288" x1="320" />
            <line x2="384" y1="-224" y2="-224" x1="320" />
            <line x2="384" y1="-160" y2="-160" x1="320" />
            <line x2="384" y1="-96" y2="-96" x1="320" />
            <line x2="384" y1="-32" y2="-32" x1="320" />
        </blockdef>
        <block symbolname="DisplaySync" name="XLXI_1">
            <blockpin signalname="clkdiv(18:17)" name="Scan(1:0)" />
            <blockpin signalname="HEXS(15:0)" name="Hexs(15:0)" />
            <blockpin signalname="points(3:0)" name="points(3:0)" />
            <blockpin signalname="LES(3:0)" name="LES(3:0)" />
            <blockpin signalname="XLXN_11(3:0)" name="HEX(3:0)" />
            <blockpin signalname="XLXN_8" name="p" />
            <blockpin signalname="XLXN_9" name="LE" />
            <blockpin signalname="AN(3:0)" name="AN(3:0)" />
        </block>
        <block symbolname="clkdiv" name="XLXI_2">
            <blockpin signalname="clk" name="clk" />
            <blockpin signalname="rst" name="rst" />
            <blockpin signalname="clkdiv(31:0)" name="clkdiv(31:0)" />
        </block>
        <block symbolname="MyMC14459" name="XLXI_3">
            <blockpin signalname="XLXN_9" name="LE" />
            <blockpin signalname="XLXN_8" name="point" />
            <blockpin signalname="XLXN_11(3)" name="D3" />
            <blockpin signalname="XLXN_11(2)" name="D2" />
            <blockpin signalname="XLXN_11(0)" name="D0" />
            <blockpin signalname="XLXN_11(1)" name="D1" />
            <blockpin signalname="SEGMENT(7)" name="p" />
            <blockpin signalname="SEGMENT(0)" name="a" />
            <blockpin signalname="SEGMENT(1)" name="b" />
            <blockpin signalname="SEGMENT(2)" name="c" />
            <blockpin signalname="SEGMENT(3)" name="d" />
            <blockpin signalname="SEGMENT(4)" name="e" />
            <blockpin signalname="SEGMENT(5)" name="f" />
            <blockpin signalname="SEGMENT(6)" name="g" />
        </block>
    </netlist>
    <sheet sheetnum="1" width="3520" height="2720">
        <instance x="944" y="896" name="XLXI_2" orien="R0">
        </instance>
        <branch name="clk">
            <wire x2="944" y1="800" y2="800" x1="912" />
        </branch>
        <iomarker fontsize="28" x="912" y="800" name="clk" orien="R180" />
        <branch name="rst">
            <wire x2="944" y1="864" y2="864" x1="912" />
        </branch>
        <iomarker fontsize="28" x="912" y="864" name="rst" orien="R180" />
        <branch name="clkdiv(31:0)">
            <wire x2="1488" y1="1216" y2="1216" x1="752" />
            <wire x2="752" y1="1216" y2="1392" x1="752" />
            <wire x2="752" y1="1392" y2="1872" x1="752" />
            <wire x2="1488" y1="800" y2="800" x1="1328" />
            <wire x2="1488" y1="800" y2="1216" x1="1488" />
        </branch>
        <branch name="HEXS(15:0)">
            <wire x2="1136" y1="1456" y2="1456" x1="576" />
        </branch>
        <branch name="points(3:0)">
            <wire x2="1136" y1="1520" y2="1520" x1="592" />
        </branch>
        <branch name="LES(3:0)">
            <wire x2="1136" y1="1584" y2="1584" x1="608" />
        </branch>
        <iomarker fontsize="28" x="576" y="1456" name="HEXS(15:0)" orien="R180" />
        <iomarker fontsize="28" x="592" y="1520" name="points(3:0)" orien="R180" />
        <iomarker fontsize="28" x="608" y="1584" name="LES(3:0)" orien="R180" />
        <instance x="2352" y="1232" name="XLXI_3" orien="R0">
        </instance>
        <branch name="XLXN_8">
            <wire x2="2336" y1="1456" y2="1456" x1="1520" />
            <wire x2="2352" y1="832" y2="832" x1="2336" />
            <wire x2="2336" y1="832" y2="1456" x1="2336" />
        </branch>
        <branch name="AN(3:0)">
            <wire x2="2544" y1="1584" y2="1584" x1="1520" />
        </branch>
        <iomarker fontsize="28" x="2544" y="1584" name="AN(3:0)" orien="R0" />
        <branch name="XLXN_11(3:0)">
            <wire x2="2160" y1="1392" y2="1392" x1="1520" />
            <wire x2="2160" y1="688" y2="912" x1="2160" />
            <wire x2="2160" y1="912" y2="992" x1="2160" />
            <wire x2="2160" y1="992" y2="1072" x1="2160" />
            <wire x2="2160" y1="1072" y2="1152" x1="2160" />
            <wire x2="2160" y1="1152" y2="1392" x1="2160" />
        </branch>
        <bustap x2="2256" y1="912" y2="912" x1="2160" />
        <branch name="XLXN_11(3)">
            <attrtext style="alignment:SOFT-BCENTER;fontsize:28;fontname:Arial" attrname="Name" x="2304" y="912" type="branch" />
            <wire x2="2304" y1="912" y2="912" x1="2256" />
            <wire x2="2352" y1="912" y2="912" x1="2304" />
        </branch>
        <bustap x2="2256" y1="992" y2="992" x1="2160" />
        <branch name="XLXN_11(2)">
            <attrtext style="alignment:SOFT-BCENTER;fontsize:28;fontname:Arial" attrname="Name" x="2304" y="992" type="branch" />
            <wire x2="2304" y1="992" y2="992" x1="2256" />
            <wire x2="2352" y1="992" y2="992" x1="2304" />
        </branch>
        <bustap x2="2256" y1="1152" y2="1152" x1="2160" />
        <branch name="XLXN_11(1)">
            <attrtext style="alignment:SOFT-BCENTER;fontsize:28;fontname:Arial" attrname="Name" x="2304" y="1152" type="branch" />
            <wire x2="2304" y1="1152" y2="1152" x1="2256" />
            <wire x2="2352" y1="1152" y2="1152" x1="2304" />
        </branch>
        <bustap x2="2256" y1="1072" y2="1072" x1="2160" />
        <branch name="XLXN_11(0)">
            <attrtext style="alignment:SOFT-BCENTER;fontsize:28;fontname:Arial" attrname="Name" x="2304" y="1072" type="branch" />
            <wire x2="2304" y1="1072" y2="1072" x1="2256" />
            <wire x2="2352" y1="1072" y2="1072" x1="2304" />
        </branch>
        <branch name="SEGMENT(7:0)">
            <wire x2="2944" y1="688" y2="752" x1="2944" />
            <wire x2="2944" y1="752" y2="816" x1="2944" />
            <wire x2="2944" y1="816" y2="880" x1="2944" />
            <wire x2="2944" y1="880" y2="944" x1="2944" />
            <wire x2="2944" y1="944" y2="976" x1="2944" />
            <wire x2="3024" y1="976" y2="976" x1="2944" />
            <wire x2="2944" y1="976" y2="1008" x1="2944" />
            <wire x2="2944" y1="1008" y2="1072" x1="2944" />
            <wire x2="2944" y1="1072" y2="1136" x1="2944" />
            <wire x2="2944" y1="1136" y2="1200" x1="2944" />
            <wire x2="2944" y1="1200" y2="1424" x1="2944" />
        </branch>
        <iomarker fontsize="28" x="3024" y="976" name="SEGMENT(7:0)" orien="R0" />
        <bustap x2="2848" y1="752" y2="752" x1="2944" />
        <branch name="SEGMENT(7)">
            <attrtext style="alignment:SOFT-LEFT;fontsize:28;fontname:Arial" attrname="Name" x="2792" y="752" type="branch" />
            <wire x2="2800" y1="752" y2="752" x1="2736" />
            <wire x2="2848" y1="752" y2="752" x1="2800" />
        </branch>
        <bustap x2="2848" y1="1200" y2="1200" x1="2944" />
        <branch name="SEGMENT(6)">
            <attrtext style="alignment:SOFT-LEFT;fontsize:28;fontname:Arial" attrname="Name" x="2792" y="1200" type="branch" />
            <wire x2="2800" y1="1200" y2="1200" x1="2736" />
            <wire x2="2848" y1="1200" y2="1200" x1="2800" />
        </branch>
        <bustap x2="2848" y1="1136" y2="1136" x1="2944" />
        <branch name="SEGMENT(5)">
            <attrtext style="alignment:SOFT-LEFT;fontsize:28;fontname:Arial" attrname="Name" x="2792" y="1136" type="branch" />
            <wire x2="2800" y1="1136" y2="1136" x1="2736" />
            <wire x2="2848" y1="1136" y2="1136" x1="2800" />
        </branch>
        <bustap x2="2848" y1="1072" y2="1072" x1="2944" />
        <branch name="SEGMENT(4)">
            <attrtext style="alignment:SOFT-LEFT;fontsize:28;fontname:Arial" attrname="Name" x="2792" y="1072" type="branch" />
            <wire x2="2800" y1="1072" y2="1072" x1="2736" />
            <wire x2="2848" y1="1072" y2="1072" x1="2800" />
        </branch>
        <bustap x2="2848" y1="944" y2="944" x1="2944" />
        <branch name="SEGMENT(2)">
            <attrtext style="alignment:SOFT-LEFT;fontsize:28;fontname:Arial" attrname="Name" x="2792" y="944" type="branch" />
            <wire x2="2800" y1="944" y2="944" x1="2736" />
            <wire x2="2848" y1="944" y2="944" x1="2800" />
        </branch>
        <bustap x2="2848" y1="880" y2="880" x1="2944" />
        <branch name="SEGMENT(1)">
            <attrtext style="alignment:SOFT-LEFT;fontsize:28;fontname:Arial" attrname="Name" x="2792" y="880" type="branch" />
            <wire x2="2800" y1="880" y2="880" x1="2736" />
            <wire x2="2848" y1="880" y2="880" x1="2800" />
        </branch>
        <bustap x2="2848" y1="816" y2="816" x1="2944" />
        <branch name="SEGMENT(0)">
            <attrtext style="alignment:SOFT-LEFT;fontsize:28;fontname:Arial" attrname="Name" x="2792" y="816" type="branch" />
            <wire x2="2800" y1="816" y2="816" x1="2736" />
            <wire x2="2848" y1="816" y2="816" x1="2800" />
        </branch>
        <bustap x2="2848" y1="1008" y2="1008" x1="2944" />
        <branch name="SEGMENT(3)">
            <attrtext style="alignment:SOFT-LEFT;fontsize:28;fontname:Arial" attrname="Name" x="2792" y="1008" type="branch" />
            <wire x2="2800" y1="1008" y2="1008" x1="2736" />
            <wire x2="2848" y1="1008" y2="1008" x1="2800" />
        </branch>
        <instance x="1136" y="1616" name="XLXI_1" orien="R0">
        </instance>
        <branch name="XLXN_9">
            <wire x2="1920" y1="1520" y2="1520" x1="1520" />
            <wire x2="1920" y1="752" y2="1520" x1="1920" />
            <wire x2="2352" y1="752" y2="752" x1="1920" />
        </branch>
        <bustap x2="848" y1="1392" y2="1392" x1="752" />
        <branch name="clkdiv(18:17)">
            <attrtext style="alignment:SOFT-BCENTER;fontsize:28;fontname:Arial" attrname="Name" x="992" y="1392" type="branch" />
            <wire x2="992" y1="1392" y2="1392" x1="848" />
            <wire x2="1136" y1="1392" y2="1392" x1="992" />
        </branch>
    </sheet>
</drawing>