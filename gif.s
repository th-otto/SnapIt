[00010000] 6000 000e                 bra.w     $00010010
[00010004] 6000 0012                 bra.w     $00010018
[00010008] 6100 04bc                 bsr       $000104C6
[0001000c] 4efa 0662                 jmp       parx_traite_fichier(pc) 00010670

[00010010] 6100 04b4                 bsr       $000104C6
[00010014] 4efa 0612                 jmp       parx_info_sauve(pc) 00010628

[00010018] 6100 04ac                 bsr       $000104C6
[0001001c] 4efa 0640                 jmp       parx_estime_taille(pc) 0001065E

[00010020] 48e7 ff44                 movem.l   d0-d7/a1/a5,-(a7)
[00010024] 3a2f 002c                 move.w    44(a7),d5
[00010028] 226f 002e                 movea.l   46(a7),a1
[0001002c] 2a6f 0032                 movea.l   50(a7),a5
[00010030] 558f                      subq.l    #2,a7
[00010032] 3e85                      move.w    d5,(a7)
[00010034] 4c99 00ff                 movem.w   (a1)+,d0-d7
[00010038] 4840                      swap      d0
[0001003a] de47                      add.w     d7,d7
[0001003c] d100                      addx.b    d0,d0
[0001003e] dc46                      add.w     d6,d6
[00010040] d100                      addx.b    d0,d0
[00010042] da45                      add.w     d5,d5
[00010044] d100                      addx.b    d0,d0
[00010046] d844                      add.w     d4,d4
[00010048] d100                      addx.b    d0,d0
[0001004a] d643                      add.w     d3,d3
[0001004c] d100                      addx.b    d0,d0
[0001004e] d442                      add.w     d2,d2
[00010050] d100                      addx.b    d0,d0
[00010052] d241                      add.w     d1,d1
[00010054] d100                      addx.b    d0,d0
[00010056] e398                      rol.l     #1,d0
[00010058] 1ac0                      move.b    d0,(a5)+
[0001005a] de47                      add.w     d7,d7
[0001005c] d100                      addx.b    d0,d0
[0001005e] dc46                      add.w     d6,d6
[00010060] d100                      addx.b    d0,d0
[00010062] da45                      add.w     d5,d5
[00010064] d100                      addx.b    d0,d0
[00010066] d844                      add.w     d4,d4
[00010068] d100                      addx.b    d0,d0
[0001006a] d643                      add.w     d3,d3
[0001006c] d100                      addx.b    d0,d0
[0001006e] d442                      add.w     d2,d2
[00010070] d100                      addx.b    d0,d0
[00010072] d241                      add.w     d1,d1
[00010074] d100                      addx.b    d0,d0
[00010076] e398                      rol.l     #1,d0
[00010078] 1ac0                      move.b    d0,(a5)+
[0001007a] de47                      add.w     d7,d7
[0001007c] d100                      addx.b    d0,d0
[0001007e] dc46                      add.w     d6,d6
[00010080] d100                      addx.b    d0,d0
[00010082] da45                      add.w     d5,d5
[00010084] d100                      addx.b    d0,d0
[00010086] d844                      add.w     d4,d4
[00010088] d100                      addx.b    d0,d0
[0001008a] d643                      add.w     d3,d3
[0001008c] d100                      addx.b    d0,d0
[0001008e] d442                      add.w     d2,d2
[00010090] d100                      addx.b    d0,d0
[00010092] d241                      add.w     d1,d1
[00010094] d100                      addx.b    d0,d0
[00010096] e398                      rol.l     #1,d0
[00010098] 1ac0                      move.b    d0,(a5)+
[0001009a] de47                      add.w     d7,d7
[0001009c] d100                      addx.b    d0,d0
[0001009e] dc46                      add.w     d6,d6
[000100a0] d100                      addx.b    d0,d0
[000100a2] da45                      add.w     d5,d5
[000100a4] d100                      addx.b    d0,d0
[000100a6] d844                      add.w     d4,d4
[000100a8] d100                      addx.b    d0,d0
[000100aa] d643                      add.w     d3,d3
[000100ac] d100                      addx.b    d0,d0
[000100ae] d442                      add.w     d2,d2
[000100b0] d100                      addx.b    d0,d0
[000100b2] d241                      add.w     d1,d1
[000100b4] d100                      addx.b    d0,d0
[000100b6] e398                      rol.l     #1,d0
[000100b8] 1ac0                      move.b    d0,(a5)+
[000100ba] de47                      add.w     d7,d7
[000100bc] d100                      addx.b    d0,d0
[000100be] dc46                      add.w     d6,d6
[000100c0] d100                      addx.b    d0,d0
[000100c2] da45                      add.w     d5,d5
[000100c4] d100                      addx.b    d0,d0
[000100c6] d844                      add.w     d4,d4
[000100c8] d100                      addx.b    d0,d0
[000100ca] d643                      add.w     d3,d3
[000100cc] d100                      addx.b    d0,d0
[000100ce] d442                      add.w     d2,d2
[000100d0] d100                      addx.b    d0,d0
[000100d2] d241                      add.w     d1,d1
[000100d4] d100                      addx.b    d0,d0
[000100d6] e398                      rol.l     #1,d0
[000100d8] 1ac0                      move.b    d0,(a5)+
[000100da] de47                      add.w     d7,d7
[000100dc] d100                      addx.b    d0,d0
[000100de] dc46                      add.w     d6,d6
[000100e0] d100                      addx.b    d0,d0
[000100e2] da45                      add.w     d5,d5
[000100e4] d100                      addx.b    d0,d0
[000100e6] d844                      add.w     d4,d4
[000100e8] d100                      addx.b    d0,d0
[000100ea] d643                      add.w     d3,d3
[000100ec] d100                      addx.b    d0,d0
[000100ee] d442                      add.w     d2,d2
[000100f0] d100                      addx.b    d0,d0
[000100f2] d241                      add.w     d1,d1
[000100f4] d100                      addx.b    d0,d0
[000100f6] e398                      rol.l     #1,d0
[000100f8] 1ac0                      move.b    d0,(a5)+
[000100fa] de47                      add.w     d7,d7
[000100fc] d100                      addx.b    d0,d0
[000100fe] dc46                      add.w     d6,d6
[00010100] d100                      addx.b    d0,d0
[00010102] da45                      add.w     d5,d5
[00010104] d100                      addx.b    d0,d0
[00010106] d844                      add.w     d4,d4
[00010108] d100                      addx.b    d0,d0
[0001010a] d643                      add.w     d3,d3
[0001010c] d100                      addx.b    d0,d0
[0001010e] d442                      add.w     d2,d2
[00010110] d100                      addx.b    d0,d0
[00010112] d241                      add.w     d1,d1
[00010114] d100                      addx.b    d0,d0
[00010116] e398                      rol.l     #1,d0
[00010118] 1ac0                      move.b    d0,(a5)+
[0001011a] de47                      add.w     d7,d7
[0001011c] d100                      addx.b    d0,d0
[0001011e] dc46                      add.w     d6,d6
[00010120] d100                      addx.b    d0,d0
[00010122] da45                      add.w     d5,d5
[00010124] d100                      addx.b    d0,d0
[00010126] d844                      add.w     d4,d4
[00010128] d100                      addx.b    d0,d0
[0001012a] d643                      add.w     d3,d3
[0001012c] d100                      addx.b    d0,d0
[0001012e] d442                      add.w     d2,d2
[00010130] d100                      addx.b    d0,d0
[00010132] d241                      add.w     d1,d1
[00010134] d100                      addx.b    d0,d0
[00010136] e398                      rol.l     #1,d0
[00010138] 1ac0                      move.b    d0,(a5)+
[0001013a] de47                      add.w     d7,d7
[0001013c] d100                      addx.b    d0,d0
[0001013e] dc46                      add.w     d6,d6
[00010140] d100                      addx.b    d0,d0
[00010142] da45                      add.w     d5,d5
[00010144] d100                      addx.b    d0,d0
[00010146] d844                      add.w     d4,d4
[00010148] d100                      addx.b    d0,d0
[0001014a] d643                      add.w     d3,d3
[0001014c] d100                      addx.b    d0,d0
[0001014e] d442                      add.w     d2,d2
[00010150] d100                      addx.b    d0,d0
[00010152] d241                      add.w     d1,d1
[00010154] d100                      addx.b    d0,d0
[00010156] e398                      rol.l     #1,d0
[00010158] 1ac0                      move.b    d0,(a5)+
[0001015a] de47                      add.w     d7,d7
[0001015c] d100                      addx.b    d0,d0
[0001015e] dc46                      add.w     d6,d6
[00010160] d100                      addx.b    d0,d0
[00010162] da45                      add.w     d5,d5
[00010164] d100                      addx.b    d0,d0
[00010166] d844                      add.w     d4,d4
[00010168] d100                      addx.b    d0,d0
[0001016a] d643                      add.w     d3,d3
[0001016c] d100                      addx.b    d0,d0
[0001016e] d442                      add.w     d2,d2
[00010170] d100                      addx.b    d0,d0
[00010172] d241                      add.w     d1,d1
[00010174] d100                      addx.b    d0,d0
[00010176] e398                      rol.l     #1,d0
[00010178] 1ac0                      move.b    d0,(a5)+
[0001017a] de47                      add.w     d7,d7
[0001017c] d100                      addx.b    d0,d0
[0001017e] dc46                      add.w     d6,d6
[00010180] d100                      addx.b    d0,d0
[00010182] da45                      add.w     d5,d5
[00010184] d100                      addx.b    d0,d0
[00010186] d844                      add.w     d4,d4
[00010188] d100                      addx.b    d0,d0
[0001018a] d643                      add.w     d3,d3
[0001018c] d100                      addx.b    d0,d0
[0001018e] d442                      add.w     d2,d2
[00010190] d100                      addx.b    d0,d0
[00010192] d241                      add.w     d1,d1
[00010194] d100                      addx.b    d0,d0
[00010196] e398                      rol.l     #1,d0
[00010198] 1ac0                      move.b    d0,(a5)+
[0001019a] de47                      add.w     d7,d7
[0001019c] d100                      addx.b    d0,d0
[0001019e] dc46                      add.w     d6,d6
[000101a0] d100                      addx.b    d0,d0
[000101a2] da45                      add.w     d5,d5
[000101a4] d100                      addx.b    d0,d0
[000101a6] d844                      add.w     d4,d4
[000101a8] d100                      addx.b    d0,d0
[000101aa] d643                      add.w     d3,d3
[000101ac] d100                      addx.b    d0,d0
[000101ae] d442                      add.w     d2,d2
[000101b0] d100                      addx.b    d0,d0
[000101b2] d241                      add.w     d1,d1
[000101b4] d100                      addx.b    d0,d0
[000101b6] e398                      rol.l     #1,d0
[000101b8] 1ac0                      move.b    d0,(a5)+
[000101ba] de47                      add.w     d7,d7
[000101bc] d100                      addx.b    d0,d0
[000101be] dc46                      add.w     d6,d6
[000101c0] d100                      addx.b    d0,d0
[000101c2] da45                      add.w     d5,d5
[000101c4] d100                      addx.b    d0,d0
[000101c6] d844                      add.w     d4,d4
[000101c8] d100                      addx.b    d0,d0
[000101ca] d643                      add.w     d3,d3
[000101cc] d100                      addx.b    d0,d0
[000101ce] d442                      add.w     d2,d2
[000101d0] d100                      addx.b    d0,d0
[000101d2] d241                      add.w     d1,d1
[000101d4] d100                      addx.b    d0,d0
[000101d6] e398                      rol.l     #1,d0
[000101d8] 1ac0                      move.b    d0,(a5)+
[000101da] de47                      add.w     d7,d7
[000101dc] d100                      addx.b    d0,d0
[000101de] dc46                      add.w     d6,d6
[000101e0] d100                      addx.b    d0,d0
[000101e2] da45                      add.w     d5,d5
[000101e4] d100                      addx.b    d0,d0
[000101e6] d844                      add.w     d4,d4
[000101e8] d100                      addx.b    d0,d0
[000101ea] d643                      add.w     d3,d3
[000101ec] d100                      addx.b    d0,d0
[000101ee] d442                      add.w     d2,d2
[000101f0] d100                      addx.b    d0,d0
[000101f2] d241                      add.w     d1,d1
[000101f4] d100                      addx.b    d0,d0
[000101f6] e398                      rol.l     #1,d0
[000101f8] 1ac0                      move.b    d0,(a5)+
[000101fa] de47                      add.w     d7,d7
[000101fc] d100                      addx.b    d0,d0
[000101fe] dc46                      add.w     d6,d6
[00010200] d100                      addx.b    d0,d0
[00010202] da45                      add.w     d5,d5
[00010204] d100                      addx.b    d0,d0
[00010206] d844                      add.w     d4,d4
[00010208] d100                      addx.b    d0,d0
[0001020a] d643                      add.w     d3,d3
[0001020c] d100                      addx.b    d0,d0
[0001020e] d442                      add.w     d2,d2
[00010210] d100                      addx.b    d0,d0
[00010212] d241                      add.w     d1,d1
[00010214] d100                      addx.b    d0,d0
[00010216] e398                      rol.l     #1,d0
[00010218] 1ac0                      move.b    d0,(a5)+
[0001021a] de47                      add.w     d7,d7
[0001021c] d100                      addx.b    d0,d0
[0001021e] dc46                      add.w     d6,d6
[00010220] d100                      addx.b    d0,d0
[00010222] da45                      add.w     d5,d5
[00010224] d100                      addx.b    d0,d0
[00010226] d844                      add.w     d4,d4
[00010228] d100                      addx.b    d0,d0
[0001022a] d643                      add.w     d3,d3
[0001022c] d100                      addx.b    d0,d0
[0001022e] d442                      add.w     d2,d2
[00010230] d100                      addx.b    d0,d0
[00010232] d241                      add.w     d1,d1
[00010234] d100                      addx.b    d0,d0
[00010236] e398                      rol.l     #1,d0
[00010238] 1ac0                      move.b    d0,(a5)+
[0001023a] 3a17                      move.w    (a7),d5
[0001023c] 51cd fdf4                 dbf       d5,$00010032
[00010240] 548f                      addq.l    #2,a7
[00010242] 4cdf 22ff                 movem.l   (a7)+,d0-d7/a1/a5
[00010246] 4e75                      rts
[00010248] 48e7 f444                 movem.l   d0-d3/d5/a1/a5,-(a7)
[0001024c] 3a2f 0020                 move.w    32(a7),d5
[00010250] 226f 0022                 movea.l   34(a7),a1
[00010254] 2a6f 0026                 movea.l   38(a7),a5
[00010258] 4c99 000f                 movem.w   (a1)+,d0-d3
[0001025c] 4840                      swap      d0
[0001025e] 4240                      clr.w     d0
[00010260] d643                      add.w     d3,d3
[00010262] d100                      addx.b    d0,d0
[00010264] d442                      add.w     d2,d2
[00010266] d100                      addx.b    d0,d0
[00010268] d241                      add.w     d1,d1
[0001026a] d100                      addx.b    d0,d0
[0001026c] e398                      rol.l     #1,d0
[0001026e] 1ac0                      move.b    d0,(a5)+
[00010270] 4240                      clr.w     d0
[00010272] d643                      add.w     d3,d3
[00010274] d100                      addx.b    d0,d0
[00010276] d442                      add.w     d2,d2
[00010278] d100                      addx.b    d0,d0
[0001027a] d241                      add.w     d1,d1
[0001027c] d100                      addx.b    d0,d0
[0001027e] e398                      rol.l     #1,d0
[00010280] 1ac0                      move.b    d0,(a5)+
[00010282] 4240                      clr.w     d0
[00010284] d643                      add.w     d3,d3
[00010286] d100                      addx.b    d0,d0
[00010288] d442                      add.w     d2,d2
[0001028a] d100                      addx.b    d0,d0
[0001028c] d241                      add.w     d1,d1
[0001028e] d100                      addx.b    d0,d0
[00010290] e398                      rol.l     #1,d0
[00010292] 1ac0                      move.b    d0,(a5)+
[00010294] 4240                      clr.w     d0
[00010296] d643                      add.w     d3,d3
[00010298] d100                      addx.b    d0,d0
[0001029a] d442                      add.w     d2,d2
[0001029c] d100                      addx.b    d0,d0
[0001029e] d241                      add.w     d1,d1
[000102a0] d100                      addx.b    d0,d0
[000102a2] e398                      rol.l     #1,d0
[000102a4] 1ac0                      move.b    d0,(a5)+
[000102a6] 4240                      clr.w     d0
[000102a8] d643                      add.w     d3,d3
[000102aa] d100                      addx.b    d0,d0
[000102ac] d442                      add.w     d2,d2
[000102ae] d100                      addx.b    d0,d0
[000102b0] d241                      add.w     d1,d1
[000102b2] d100                      addx.b    d0,d0
[000102b4] e398                      rol.l     #1,d0
[000102b6] 1ac0                      move.b    d0,(a5)+
[000102b8] 4240                      clr.w     d0
[000102ba] d643                      add.w     d3,d3
[000102bc] d100                      addx.b    d0,d0
[000102be] d442                      add.w     d2,d2
[000102c0] d100                      addx.b    d0,d0
[000102c2] d241                      add.w     d1,d1
[000102c4] d100                      addx.b    d0,d0
[000102c6] e398                      rol.l     #1,d0
[000102c8] 1ac0                      move.b    d0,(a5)+
[000102ca] 4240                      clr.w     d0
[000102cc] d643                      add.w     d3,d3
[000102ce] d100                      addx.b    d0,d0
[000102d0] d442                      add.w     d2,d2
[000102d2] d100                      addx.b    d0,d0
[000102d4] d241                      add.w     d1,d1
[000102d6] d100                      addx.b    d0,d0
[000102d8] e398                      rol.l     #1,d0
[000102da] 1ac0                      move.b    d0,(a5)+
[000102dc] 4240                      clr.w     d0
[000102de] d643                      add.w     d3,d3
[000102e0] d100                      addx.b    d0,d0
[000102e2] d442                      add.w     d2,d2
[000102e4] d100                      addx.b    d0,d0
[000102e6] d241                      add.w     d1,d1
[000102e8] d100                      addx.b    d0,d0
[000102ea] e398                      rol.l     #1,d0
[000102ec] 1ac0                      move.b    d0,(a5)+
[000102ee] 4240                      clr.w     d0
[000102f0] d643                      add.w     d3,d3
[000102f2] d100                      addx.b    d0,d0
[000102f4] d442                      add.w     d2,d2
[000102f6] d100                      addx.b    d0,d0
[000102f8] d241                      add.w     d1,d1
[000102fa] d100                      addx.b    d0,d0
[000102fc] e398                      rol.l     #1,d0
[000102fe] 1ac0                      move.b    d0,(a5)+
[00010300] 4240                      clr.w     d0
[00010302] d643                      add.w     d3,d3
[00010304] d100                      addx.b    d0,d0
[00010306] d442                      add.w     d2,d2
[00010308] d100                      addx.b    d0,d0
[0001030a] d241                      add.w     d1,d1
[0001030c] d100                      addx.b    d0,d0
[0001030e] e398                      rol.l     #1,d0
[00010310] 1ac0                      move.b    d0,(a5)+
[00010312] 4240                      clr.w     d0
[00010314] d643                      add.w     d3,d3
[00010316] d100                      addx.b    d0,d0
[00010318] d442                      add.w     d2,d2
[0001031a] d100                      addx.b    d0,d0
[0001031c] d241                      add.w     d1,d1
[0001031e] d100                      addx.b    d0,d0
[00010320] e398                      rol.l     #1,d0
[00010322] 1ac0                      move.b    d0,(a5)+
[00010324] 4240                      clr.w     d0
[00010326] d643                      add.w     d3,d3
[00010328] d100                      addx.b    d0,d0
[0001032a] d442                      add.w     d2,d2
[0001032c] d100                      addx.b    d0,d0
[0001032e] d241                      add.w     d1,d1
[00010330] d100                      addx.b    d0,d0
[00010332] e398                      rol.l     #1,d0
[00010334] 1ac0                      move.b    d0,(a5)+
[00010336] 4240                      clr.w     d0
[00010338] d643                      add.w     d3,d3
[0001033a] d100                      addx.b    d0,d0
[0001033c] d442                      add.w     d2,d2
[0001033e] d100                      addx.b    d0,d0
[00010340] d241                      add.w     d1,d1
[00010342] d100                      addx.b    d0,d0
[00010344] e398                      rol.l     #1,d0
[00010346] 1ac0                      move.b    d0,(a5)+
[00010348] 4240                      clr.w     d0
[0001034a] d643                      add.w     d3,d3
[0001034c] d100                      addx.b    d0,d0
[0001034e] d442                      add.w     d2,d2
[00010350] d100                      addx.b    d0,d0
[00010352] d241                      add.w     d1,d1
[00010354] d100                      addx.b    d0,d0
[00010356] e398                      rol.l     #1,d0
[00010358] 1ac0                      move.b    d0,(a5)+
[0001035a] 4240                      clr.w     d0
[0001035c] d643                      add.w     d3,d3
[0001035e] d100                      addx.b    d0,d0
[00010360] d442                      add.w     d2,d2
[00010362] d100                      addx.b    d0,d0
[00010364] d241                      add.w     d1,d1
[00010366] d100                      addx.b    d0,d0
[00010368] e398                      rol.l     #1,d0
[0001036a] 1ac0                      move.b    d0,(a5)+
[0001036c] 4240                      clr.w     d0
[0001036e] d643                      add.w     d3,d3
[00010370] d100                      addx.b    d0,d0
[00010372] d442                      add.w     d2,d2
[00010374] d100                      addx.b    d0,d0
[00010376] d241                      add.w     d1,d1
[00010378] d100                      addx.b    d0,d0
[0001037a] e398                      rol.l     #1,d0
[0001037c] 1ac0                      move.b    d0,(a5)+
[0001037e] 51cd fed8                 dbf       d5,$00010258
[00010382] 4cdf 222f                 movem.l   (a7)+,d0-d3/d5/a1/a5
[00010386] 4e75                      rts
[00010388] 48e7 c444                 movem.l   d0-d1/d5/a1/a5,-(a7)
[0001038c] 3a2f 0018                 move.w    24(a7),d5
[00010390] 226f 001a                 movea.l   26(a7),a1
[00010394] 2a6f 001e                 movea.l   30(a7),a5
[00010398] 4c99 0003                 movem.w   (a1)+,d0-d1
[0001039c] 4840                      swap      d0
[0001039e] 4240                      clr.w     d0
[000103a0] d241                      add.w     d1,d1
[000103a2] d100                      addx.b    d0,d0
[000103a4] e398                      rol.l     #1,d0
[000103a6] 1ac0                      move.b    d0,(a5)+
[000103a8] 4240                      clr.w     d0
[000103aa] d241                      add.w     d1,d1
[000103ac] d100                      addx.b    d0,d0
[000103ae] e398                      rol.l     #1,d0
[000103b0] 1ac0                      move.b    d0,(a5)+
[000103b2] 4240                      clr.w     d0
[000103b4] d241                      add.w     d1,d1
[000103b6] d100                      addx.b    d0,d0
[000103b8] e398                      rol.l     #1,d0
[000103ba] 1ac0                      move.b    d0,(a5)+
[000103bc] 4240                      clr.w     d0
[000103be] d241                      add.w     d1,d1
[000103c0] d100                      addx.b    d0,d0
[000103c2] e398                      rol.l     #1,d0
[000103c4] 1ac0                      move.b    d0,(a5)+
[000103c6] 4240                      clr.w     d0
[000103c8] d241                      add.w     d1,d1
[000103ca] d100                      addx.b    d0,d0
[000103cc] e398                      rol.l     #1,d0
[000103ce] 1ac0                      move.b    d0,(a5)+
[000103d0] 4240                      clr.w     d0
[000103d2] d241                      add.w     d1,d1
[000103d4] d100                      addx.b    d0,d0
[000103d6] e398                      rol.l     #1,d0
[000103d8] 1ac0                      move.b    d0,(a5)+
[000103da] 4240                      clr.w     d0
[000103dc] d241                      add.w     d1,d1
[000103de] d100                      addx.b    d0,d0
[000103e0] e398                      rol.l     #1,d0
[000103e2] 1ac0                      move.b    d0,(a5)+
[000103e4] 4240                      clr.w     d0
[000103e6] d241                      add.w     d1,d1
[000103e8] d100                      addx.b    d0,d0
[000103ea] e398                      rol.l     #1,d0
[000103ec] 1ac0                      move.b    d0,(a5)+
[000103ee] 4240                      clr.w     d0
[000103f0] d241                      add.w     d1,d1
[000103f2] d100                      addx.b    d0,d0
[000103f4] e398                      rol.l     #1,d0
[000103f6] 1ac0                      move.b    d0,(a5)+
[000103f8] 4240                      clr.w     d0
[000103fa] d241                      add.w     d1,d1
[000103fc] d100                      addx.b    d0,d0
[000103fe] e398                      rol.l     #1,d0
[00010400] 1ac0                      move.b    d0,(a5)+
[00010402] 4240                      clr.w     d0
[00010404] d241                      add.w     d1,d1
[00010406] d100                      addx.b    d0,d0
[00010408] e398                      rol.l     #1,d0
[0001040a] 1ac0                      move.b    d0,(a5)+
[0001040c] 4240                      clr.w     d0
[0001040e] d241                      add.w     d1,d1
[00010410] d100                      addx.b    d0,d0
[00010412] e398                      rol.l     #1,d0
[00010414] 1ac0                      move.b    d0,(a5)+
[00010416] 4240                      clr.w     d0
[00010418] d241                      add.w     d1,d1
[0001041a] d100                      addx.b    d0,d0
[0001041c] e398                      rol.l     #1,d0
[0001041e] 1ac0                      move.b    d0,(a5)+
[00010420] 4240                      clr.w     d0
[00010422] d241                      add.w     d1,d1
[00010424] d100                      addx.b    d0,d0
[00010426] e398                      rol.l     #1,d0
[00010428] 1ac0                      move.b    d0,(a5)+
[0001042a] 4240                      clr.w     d0
[0001042c] d241                      add.w     d1,d1
[0001042e] d100                      addx.b    d0,d0
[00010430] e398                      rol.l     #1,d0
[00010432] 1ac0                      move.b    d0,(a5)+
[00010434] 4240                      clr.w     d0
[00010436] d241                      add.w     d1,d1
[00010438] d100                      addx.b    d0,d0
[0001043a] e398                      rol.l     #1,d0
[0001043c] 1ac0                      move.b    d0,(a5)+
[0001043e] 51cd ff58                 dbf       d5,$00010398
[00010442] 4cdf 2223                 movem.l   (a7)+,d0-d1/d5/a1/a5
[00010446] 4e75                      rts
[00010448] 48e7 8444                 movem.l   d0/d5/a1/a5,-(a7)
[0001044c] 3a2f 0014                 move.w    20(a7),d5
[00010450] 226f 0016                 movea.l   22(a7),a1
[00010454] 2a6f 001a                 movea.l   26(a7),a5
[00010458] 3019                      move.w    (a1)+,d0
[0001045a] 4840                      swap      d0
[0001045c] 4240                      clr.w     d0
[0001045e] e398                      rol.l     #1,d0
[00010460] 1ac0                      move.b    d0,(a5)+
[00010462] 4240                      clr.w     d0
[00010464] e398                      rol.l     #1,d0
[00010466] 1ac0                      move.b    d0,(a5)+
[00010468] 4240                      clr.w     d0
[0001046a] e398                      rol.l     #1,d0
[0001046c] 1ac0                      move.b    d0,(a5)+
[0001046e] 4240                      clr.w     d0
[00010470] e398                      rol.l     #1,d0
[00010472] 1ac0                      move.b    d0,(a5)+
[00010474] 4240                      clr.w     d0
[00010476] e398                      rol.l     #1,d0
[00010478] 1ac0                      move.b    d0,(a5)+
[0001047a] 4240                      clr.w     d0
[0001047c] e398                      rol.l     #1,d0
[0001047e] 1ac0                      move.b    d0,(a5)+
[00010480] 4240                      clr.w     d0
[00010482] e398                      rol.l     #1,d0
[00010484] 1ac0                      move.b    d0,(a5)+
[00010486] 4240                      clr.w     d0
[00010488] e398                      rol.l     #1,d0
[0001048a] 1ac0                      move.b    d0,(a5)+
[0001048c] 4240                      clr.w     d0
[0001048e] e398                      rol.l     #1,d0
[00010490] 1ac0                      move.b    d0,(a5)+
[00010492] 4240                      clr.w     d0
[00010494] e398                      rol.l     #1,d0
[00010496] 1ac0                      move.b    d0,(a5)+
[00010498] 4240                      clr.w     d0
[0001049a] e398                      rol.l     #1,d0
[0001049c] 1ac0                      move.b    d0,(a5)+
[0001049e] 4240                      clr.w     d0
[000104a0] e398                      rol.l     #1,d0
[000104a2] 1ac0                      move.b    d0,(a5)+
[000104a4] 4240                      clr.w     d0
[000104a6] e398                      rol.l     #1,d0
[000104a8] 1ac0                      move.b    d0,(a5)+
[000104aa] 4240                      clr.w     d0
[000104ac] e398                      rol.l     #1,d0
[000104ae] 1ac0                      move.b    d0,(a5)+
[000104b0] 4240                      clr.w     d0
[000104b2] e398                      rol.l     #1,d0
[000104b4] 1ac0                      move.b    d0,(a5)+
[000104b6] 4240                      clr.w     d0
[000104b8] e398                      rol.l     #1,d0
[000104ba] 1ac0                      move.b    d0,(a5)+
[000104bc] 51cd ff9a                 dbf       d5,$00010458
[000104c0] 4cdf 2221                 movem.l   (a7)+,d0/d5/a1/a5
[000104c4] 4e75                      rts


[000104c6] 48e7 6040                 movem.l   d1-d2/a1,-(a7)
[000104ca] 43fa 003e                 lea.l     $0001050A(pc),a1
[000104ce] 2411                      move.l    (a1),d2
[000104d0] 41fa faf6                 lea.l     $0000FFC8(pc),a0
[000104d4] 2208                      move.l    a0,d1
[000104d6] b481                      cmp.l     d1,d2
[000104d8] 672a                      beq.s     $00010504
[000104da] 2281                      move.l    d1,(a1)
[000104dc] 2248                      movea.l   a0,a1
[000104de] d3fa 002e                 adda.l    $0001050E(pc),a1
[000104e2] 2019                      move.l    (a1)+,d0
[000104e4] 671e                      beq.s     $00010504
[000104e6] d1c0                      adda.l    d0,a0
[000104e8] 9282                      sub.l     d2,d1
[000104ea] d390                      add.l     d1,(a0)
[000104ec] 7000                      moveq.l   #0,d0
[000104ee] 1019                      move.b    (a1)+,d0
[000104f0] 6712                      beq.s     $00010504
[000104f2] b03c 0001                 cmp.b     #$01,d0
[000104f6] 6706                      beq.s     $000104FE
[000104f8] d0c0                      adda.w    d0,a0
[000104fa] d390                      add.l     d1,(a0)
[000104fc] 60f0                      bra.s     $000104EE
[000104fe] d0fc 00fe                 adda.w    #$00FE,a0
[00010502] 60ea                      bra.s     $000104EE
[00010504] 4cdf 0206                 movem.l   (a7)+,d1-d2/a1
[00010508] 4e75                      rts
[0001050a] 0000 0000                 ori.b     #$00,d0
[0001050e] 0000 0dd4                 ori.b     #$D4,d0
[00010512] 0002 0306                 ori.b     #$06,d2
[00010516] 0407 0508                 subi.b    #$08,d7
[0001051a] 090a 0b0e                 movep.w   2830(a2),d4
[0001051e] 0c0f 0dff                 cmpi.b    #$FF,a7 ; apollo only
[00010522] 1011                      move.b    (a1),d0
[00010524] 1213                      move.b    (a3),d1
[00010526] 1415                      move.b    (a5),d2
[00010528] 1617                      move.b    (a7),d3
[0001052a] 1819                      move.b    (a1)+,d4
[0001052c] 1a1b                      move.b    (a3)+,d5
[0001052e] 1c1d                      move.b    (a5)+,d6
[00010530] 1e1f                      move.b    (a7)+,d7
[00010532] 2021                      move.l    -(a1),d0
[00010534] 2223                      move.l    -(a3),d1
[00010536] 2425                      move.l    -(a5),d2
[00010538] 2627                      move.l    -(a7),d3
[0001053a] 2829 2a2b                 move.l    10795(a1),d4
[0001053e] 2c2d 2e2f                 move.l    11823(a5),d6
[00010542] 3031 3233                 move.w    51(a1,d3.w*2),d0 ; 68020+ only
[00010546] 3435 3637                 move.w    55(a5,d3.w*8),d2 ; 68020+ only
[0001054a] 3839 3a3b 3c3d            move.w    $3A3B3C3D,d4
[00010550] 3e3f                      move.w    ???,d7
[00010552] 4041                      negx.w    d1
[00010554] 4243                      clr.w     d3
[00010556] 4445                      neg.w     d5
[00010558] 4647                      not.w     d7
[0001055a] 4849                      bkpt      #1
[0001055c] 4a4b                      tst.w     a3
[0001055e] 4c4d 4e4f                 divs.l    a5,a7:d4 ; apollo only
[00010562] 5051                      addq.w    #8,(a1)
[00010564] 5253                      addq.w    #1,(a3)
[00010566] 5455                      addq.w    #2,(a5)
[00010568] 5657                      addq.w    #3,(a7)
[0001056a] 5859                      addq.w    #4,(a1)+
[0001056c] 5a5b                      addq.w    #5,(a3)+
[0001056e] 5c5d                      addq.w    #6,(a5)+
[00010570] 5e5f                      addq.w    #7,(a7)+
[00010572] 6061                      bra.s     $000105D5
[00010574] 6263                      bhi.s     $000105D9
[00010576] 6465                      bcc.s     $000105DD
[00010578] 6667                      bne.s     $000105E1
[0001057a] 6869                      bvc.s     $000105E5
[0001057c] 6a6b                      bpl.s     $000105E9
[0001057e] 6c6d                      bge.s     $000105ED
[00010580] 6e6f                      bgt.s     $000105F1
[00010582] 7071                      moveq.l   #113,d0
[00010584] 7273                      moveq.l   #115,d1
[00010586] 7475                      moveq.l   #117,d2
[00010588] 7677                      moveq.l   #119,d3
[0001058a] 7879                      moveq.l   #121,d4
[0001058c] 7a7b                      moveq.l   #123,d5
[0001058e] 7c7d                      moveq.l   #125,d6
[00010590] 7e7f                      moveq.l   #127,d7
[00010592] 8081                      or.l      d1,d0
[00010594] 8283                      or.l      d3,d1
[00010596] 8485                      or.l      d5,d2
[00010598] 8687                      or.l      d7,d3
[0001059a] 8889                      or.l      a1,d4 ; apollo only
[0001059c] 8a8b                      or.l      a3,d5 ; apollo only
[0001059e] 8c8d                      or.l      a5,d6 ; apollo only
[000105a0] 8e8f                      or.l      a7,d7 ; apollo only
[000105a2] 9091                      sub.l     (a1),d0
[000105a4] 9293                      sub.l     (a3),d1
[000105a6] 9495                      sub.l     (a5),d2
[000105a8] 9697                      sub.l     (a7),d3
[000105aa] 9899                      sub.l     (a1)+,d4
[000105ac] 9a9b                      sub.l     (a3)+,d5
[000105ae] 9c9d                      sub.l     (a5)+,d6
[000105b0] 9e9f                      sub.l     (a7)+,d7
[000105b2] a0a1 a2a3                 mac.w     d3.l,a2.u,<<1,-(a1)&,d0,acc0
[000105b6] a4a5 a6a7                 mac.w     d7.l,a2.u,>>1,-(a5)&,d2,acc0
[000105ba] a8a9 aaab acad            mac.l     a3,a2,<<1,-21331(a1)&,d4,acc0
[000105c0] aeaf b0b1 b2b3            mac.w     d1.l,a3.u,0,-19789(a7)&,d7,acc2
[000105c6] b4b5 b6b7                 cmp.l     -73(a5,a3.w*8),d2 ; 68020+ only
[000105ca] b8b9 babb bcbd            cmp.l     $BABBBCBD,d4
[000105d0] bebf                      cmp.l     ???,d7
[000105d2] c0c1                      mulu.w    d1,d0
[000105d4] c2c3                      mulu.w    d3,d1
[000105d6] c4c5                      mulu.w    d5,d2
[000105d8] c6c7                      mulu.w    d7,d3
[000105da] c8c9                      mulu.w    a1,d4
[000105dc] cacb                      mulu.w    a3,d5
[000105de] cccd                      mulu.w    a5,d6
[000105e0] cecf                      mulu.w    a7,d7
[000105e2] d0d1                      adda.w    (a1),a0
[000105e4] d2d3                      adda.w    (a3),a1
[000105e6] d4d5                      adda.w    (a5),a2
[000105e8] d6d7                      adda.w    (a7),a3
[000105ea] d8d9                      adda.w    (a1)+,a4
[000105ec] dadb                      adda.w    (a3)+,a5
[000105ee] dcdd                      adda.w    (a5)+,a6
[000105f0] dedf                      adda.w    (a7)+,a7
[000105f2] e0e1                      asr.w     -(a1)
[000105f4] e2e3                      lsr.w     -(a3)
[000105f6] e4e5                      roxr.w    -(a5)
[000105f8] e6e7                      ror.w     -(a7)
[000105fa] e8e9 eaeb eced            bftst     -4883(a1){d?:d?} ; 68020+ only
[00010600] eeef f0f1 f2f3            bfset     -3341(a7){3:d?} ; 68020+ only
[00010606] f4f5                      cpushp    bc,(a5)
[00010608] f6f7                      dc.w      $F6F7 ; illegal
[0001060a] f8f9 fafb fcfd            lpB??.l   $FAFD0309
[00010610] fe01 0002                 transhi.q d1-d4,d0:d1
[00010614] 0306                      btst      d1,d6
[00010616] 0407 0508                 subi.b    #$08,d7
[0001061a] 090a 0b0e                 movep.w   2830(a2),d4
[0001061e] 0c0f 0d01                 cmpi.b    #$01,a7 ; apollo only
[00010622] 0002 0301                 ori.b     #$01,d2
[00010626] 0001                  ori.b     #$6F,d1

parx_info_sauve:
[00010628] 206f 0004                 movea.l   4(a7),a0
[0001062c] 20bc 2e47 4946            move.l    #$2e474946,(a0)
[00010632] 3028 000c                 move.w    12(a0),d0
[00010636] b07c 0001                 cmp.w     #$0001,d0
[0001063a] 6604                      bne.s     $00010640
[0001063c] 7201                      moveq.l   #1,d1
[0001063e] 6016                      bra.s     $00010656
[00010640] b07c 0002                 cmp.w     #$0002,d0
[00010644] 6604                      bne.s     $0001064A
[00010646] 7202                      moveq.l   #2,d1
[00010648] 600c                      bra.s     $00010656
[0001064a] b07c 0004                 cmp.w     #$0004,d0
[0001064e] 6e04                      bgt.s     $00010654
[00010650] 7204                      moveq.l   #4,d1
[00010652] 6002                      bra.s     $00010656
[00010654] 7208                      moveq.l   #8,d1
[00010656] 3141 000c                 move.w    d1,12(a0)
[0001065a] 7001                      moveq.l   #1,d0
[0001065c] 4e75                      rts

parx_estime_taille:
[0001065e] 206f 0004                 movea.l   4(a7),a0
[00010662] 3028 0004                 move.w    4(a0),d0
[00010666] 48c0                      ext.l     d0
[00010668] d0bc 0000 8556            add.l     #$00008556,d0
[0001066e] 4e75                      rts

parx_traite_fichier:
[00010670] 48e7 2030                 movem.l   d2/a2-a3,-(a7)
[00010674] 246f 0010                 movea.l   16(a7),a2
[00010678] 206f 0018                 movea.l   24(a7),a0
[0001067c] 302a 000c                 move.w    12(a2),d0
[00010680] b07c 0001                 cmp.w     #$0001,d0
[00010684] 6716                      beq.s     $0001069C
[00010686] b07c 0002                 cmp.w     #$0002,d0
[0001068a] 6710                      beq.s     $0001069C
[0001068c] b07c 0004                 cmp.w     #$0004,d0
[00010690] 670a                      beq.s     $0001069C
[00010692] b07c 0008                 cmp.w     #$0008,d0
[00010696] 6704                      beq.s     $0001069C
[00010698] 70ff                      moveq.l   #-1,d0
[0001069a] 606e                      bra.s     $0001070A
[0001069c] 43f9 0000 0d8c            lea.l     $00000D8C,a1
[000106a2] 2288                      move.l    a0,(a1)
[000106a4] 336a 000e fffc            move.w    14(a2),-4(a1)
[000106aa] 4269 0004                 clr.w     4(a1)
[000106ae] 4269 fffe                 clr.w     -2(a1)
[000106b2] 4269 000e                 clr.w     14(a1)
[000106b6] 2352 001a                 move.l    (a2),26(a1)
[000106ba] 336a 0004 000a            move.w    4(a2),10(a1)
[000106c0] 336a 0006 000c            move.w    6(a2),12(a1)
[000106c6] 70ff                      moveq.l   #-1,d0
[000106c8] d06a 0008                 add.w     8(a2),d0
[000106cc] 3340 0010                 move.w    d0,16(a1)
[000106d0] 322a 000c                 move.w    12(a2),d1
[000106d4] d241                      add.w     d1,d1
[000106d6] c3ea 0008                 muls.w    8(a2),d1
[000106da] 48c1                      ext.l     d1
[000106dc] 2341 0012                 move.l    d1,18(a1)
[000106e0] 41e8 1004                 lea.l     4100(a0),a0
[000106e4] 2348 0022                 move.l    a0,34(a1)
[000106e8] 41e8 4e2c                 lea.l     20012(a0),a0
[000106ec] 2348 0026                 move.l    a0,38(a1)
[000106f0] 47e8 2716                 lea.l     10006(a0),a3
[000106f4] 234b 0016                 move.l    a3,22(a1)
[000106f8] 206f 0014                 movea.l   20(a7),a0
[000106fc] 4242                      clr.w     d2
[000106fe] 302a 000c                 move.w    12(a2),d0
[00010702] 72ff                      moveq.l   #-1,d1
[00010704] 6100 00a0                 bsr       $000107A6
[00010708] 48c0                      ext.l     d0
[0001070a] 4cdf 0c04                 movem.l   (a7)+,d2/a2-a3
[0001070e] 4e75                      rts
[00010710] 2f0a                      move.l    a2,-(a7)
[00010712] 45f9 0000 0dba            lea.l     $00000DBA,a2
[00010718] 24aa ffe8                 move.l    -24(a2),(a2)
[0001071c] 2f12                      move.l    (a2),-(a7)
[0001071e] 302a fffe                 move.w    -2(a2),d0
[00010722] 48c0                      ext.l     d0
[00010724] 222a ffe4                 move.l    -28(a2),d1
[00010728] 6100 058e                 bsr       $00010CB8
[0001072c] 206a ffec                 movea.l   -20(a2),a0
[00010730] 4870 0800                 pea.l     0(a0,d0.l)
[00010734] 3f2a ffe2                 move.w    -30(a2),-(a7)
[00010738] 206a fff0                 movea.l   -16(a2),a0
[0001073c] 4e90                      jsr       (a0)
[0001073e] 4fef 000a                 lea.l     10(a7),a7
[00010742] 245f                      movea.l   (a7)+,a2
[00010744] 4e75                      rts
[00010746] 2f0a                      move.l    a2,-(a7)
[00010748] 45f9 0000 0db6            lea.l     $00000DB6,a2
[0001074e] 3012                      move.w    (a2),d0
[00010750] b06a ffe0                 cmp.w     -32(a2),d0
[00010754] 663e                      bne.s     $00010794
[00010756] 4252                      clr.w     (a2)
[00010758] 41f9 0000 0d2a            lea.l     $00000D2A,a0
[0001075e] 302a 0008                 move.w    8(a2),d0
[00010762] 1230 0000                 move.b    0(a0,d0.w),d1
[00010766] 4881                      ext.w     d1
[00010768] d36a 0002                 add.w     d1,2(a2)
[0001076c] 302a 0002                 move.w    2(a2),d0
[00010770] b06a ffe2                 cmp.w     -30(a2),d0
[00010774] 6d1a                      blt.s     $00010790
[00010776] 322a 0008                 move.w    8(a2),d1
[0001077a] 1430 1005                 move.b    5(a0,d1.w),d2
[0001077e] 4882                      ext.w     d2
[00010780] 3542 0002                 move.w    d2,2(a2)
[00010784] 5242                      addq.w    #1,d2
[00010786] 6604                      bne.s     $0001078C
[00010788] 70ff                      moveq.l   #-1,d0
[0001078a] 6016                      bra.s     $000107A2
[0001078c] 526a 0008                 addq.w    #1,8(a2)
[00010790] 6100 ff7e                 bsr       $00010710
[00010794] 5252                      addq.w    #1,(a2)
[00010796] 206a 0004                 movea.l   4(a2),a0
[0001079a] 52aa 0004                 addq.l    #1,4(a2)
[0001079e] 4240                      clr.w     d0
[000107a0] 1010                      move.b    (a0),d0
[000107a2] 245f                      movea.l   (a7)+,a2
[000107a4] 4e75                      rts
[000107a6] 48e7 1f3c                 movem.l   d3-d7/a2-a5,-(a7)
[000107aa] 4fef fff6                 lea.l     -10(a7),a7
[000107ae] 3600                      move.w    d0,d3
[000107b0] 3c01                      move.w    d1,d6
[000107b2] 3e02                      move.w    d2,d7
[000107b4] 2848                      movea.l   a0,a4
[000107b6] 47f9 0000 0daa            lea.l     $00000DAA,a3
[000107bc] 3f6b ffec 0008            move.w    -20(a3),8(a7)
[000107c2] 3f6b ffee 0006            move.w    -18(a3),6(a7)
[000107c8] 4240                      clr.w     d0
[000107ca] 3f40 0002                 move.w    d0,2(a7)
[000107ce] 3f40 0004                 move.w    d0,4(a7)
[000107d2] 3e83                      move.w    d3,(a7)
[000107d4] b67c 0001                 cmp.w     #$0001,d3
[000107d8] 6e04                      bgt.s     $000107DE
[000107da] 7a02                      moveq.l   #2,d5
[000107dc] 6002                      bra.s     $000107E0
[000107de] 3a03                      move.w    d3,d5
[000107e0] 4a46                      tst.w     d6
[000107e2] 6a08                      bpl.s     $000107EC
[000107e4] 41f9 0000 0d7a            lea.l     $00000D7A,a0
[000107ea] 6006                      bra.s     $000107F2
[000107ec] 41f9 0000 0d81            lea.l     $00000D81,a0
[000107f2] 7206                      moveq.l   #6,d1
[000107f4] 302b ffde                 move.w    -34(a3),d0
[000107f8] 6100 04e6                 bsr       $00010CE0
[000107fc] 7206                      moveq.l   #6,d1
[000107fe] b280                      cmp.l     d0,d1
[00010800] 6706                      beq.s     $00010808
[00010802] 70ff                      moveq.l   #-1,d0
[00010804] 6000 018a                 bra       $00010990
[00010808] 41ef 0008                 lea.l     8(a7),a0
[0001080c] 6100 018c                 bsr       $0001099A
[00010810] 41ef 0006                 lea.l     6(a7),a0
[00010814] 6100 0184                 bsr       $0001099A
[00010818] 383c 0080                 move.w    #$0080,d4
[0001081c] 70ff                      moveq.l   #-1,d0
[0001081e] d057                      add.w     (a7),d0
[00010820] eb48                      lsl.w     #5,d0
[00010822] 8840                      or.w      d0,d4
[00010824] 72ff                      moveq.l   #-1,d1
[00010826] d243                      add.w     d3,d1
[00010828] 8841                      or.w      d1,d4
[0001082a] 1004                      move.b    d4,d0
[0001082c] 6100 0442                 bsr       $00010C70
[00010830] 1007                      move.b    d7,d0
[00010832] 6100 043c                 bsr       $00010C70
[00010836] 4200                      clr.b     d0
[00010838] 6100 0436                 bsr       $00010C70
[0001083c] b67c 0001                 cmp.w     #$0001,d3
[00010840] 660e                      bne.s     $00010850
[00010842] 45f9 0000 065e            lea.l     $0000065E,a2
[00010848] 26bc 0000 0480            move.l    #$00000480,(a3)
[0001084e] 6034                      bra.s     $00010884
[00010850] b67c 0002                 cmp.w     #$0002,d3
[00010854] 660e                      bne.s     $00010864
[00010856] 45f9 0000 065a            lea.l     $0000065A,a2
[0001085c] 26bc 0000 03c0            move.l    #$000003C0,(a3)
[00010862] 6020                      bra.s     $00010884
[00010864] b67c 0004                 cmp.w     #$0004,d3
[00010868] 660e                      bne.s     $00010878
[0001086a] 45f9 0000 064a            lea.l     $0000064A,a2
[00010870] 26bc 0000 0280            move.l    #$00000280,(a3)
[00010876] 600c                      bra.s     $00010884
[00010878] 45f9 0000 054a            lea.l     $0000054A,a2
[0001087e] 26bc 0000 0058            move.l    #$00000058,(a3)
[00010884] 7e01                      moveq.l   #1,d7
[00010886] e76f                      lsl.w     d3,d7
[00010888] 4244                      clr.w     d4
[0001088a] 6056                      bra.s     $000108E2
[0001088c] 4241                      clr.w     d1
[0001088e] 1232 4000                 move.b    0(a2,d4.w),d1
[00010892] 3001                      move.w    d1,d0
[00010894] d040                      add.w     d0,d0
[00010896] d041                      add.w     d1,d0
[00010898] 48c0                      ext.l     d0
[0001089a] d080                      add.l     d0,d0
[0001089c] 4bf4 0800                 lea.l     0(a4,d0.l),a5
[000108a0] 7433                      moveq.l   #51,d2
[000108a2] c4dd                      mulu.w    (a5)+,d2
[000108a4] d47c 0064                 add.w     #$0064,d2
[000108a8] 7000                      moveq.l   #0,d0
[000108aa] 3002                      move.w    d2,d0
[000108ac] 80fc 00c8                 divu.w    #$00C8,d0
[000108b0] 6100 03be                 bsr       $00010C70
[000108b4] 7033                      moveq.l   #51,d0
[000108b6] c0dd                      mulu.w    (a5)+,d0
[000108b8] d07c 0064                 add.w     #$0064,d0
[000108bc] 7200                      moveq.l   #0,d1
[000108be] 3200                      move.w    d0,d1
[000108c0] 2001                      move.l    d1,d0
[000108c2] 80fc 00c8                 divu.w    #$00C8,d0
[000108c6] 6100 03a8                 bsr       $00010C70
[000108ca] 7033                      moveq.l   #51,d0
[000108cc] c0d5                      mulu.w    (a5),d0
[000108ce] d07c 0064                 add.w     #$0064,d0
[000108d2] 7200                      moveq.l   #0,d1
[000108d4] 3200                      move.w    d0,d1
[000108d6] 2001                      move.l    d1,d0
[000108d8] 80fc 00c8                 divu.w    #$00C8,d0
[000108dc] 6100 0392                 bsr       $00010C70
[000108e0] 5244                      addq.w    #1,d4
[000108e2] be44                      cmp.w     d4,d7
[000108e4] 6ea6                      bgt.s     $0001088C
[000108e6] 4a46                      tst.w     d6
[000108e8] 6b30                      bmi.s     $0001091A
[000108ea] 7021                      moveq.l   #33,d0
[000108ec] 6100 0382                 bsr       $00010C70
[000108f0] 70f9                      moveq.l   #-7,d0
[000108f2] 6100 037c                 bsr       $00010C70
[000108f6] 7004                      moveq.l   #4,d0
[000108f8] 6100 0376                 bsr       $00010C70
[000108fc] 7001                      moveq.l   #1,d0
[000108fe] 6100 0370                 bsr       $00010C70
[00010902] 4200                      clr.b     d0
[00010904] 6100 036a                 bsr       $00010C70
[00010908] 4200                      clr.b     d0
[0001090a] 6100 0364                 bsr       $00010C70
[0001090e] 1006                      move.b    d6,d0
[00010910] 6100 035e                 bsr       $00010C70
[00010914] 4200                      clr.b     d0
[00010916] 6100 0358                 bsr       $00010C70
[0001091a] 702c                      moveq.l   #44,d0
[0001091c] 6100 0352                 bsr       $00010C70
[00010920] 41ef 0004                 lea.l     4(a7),a0
[00010924] 6100 0074                 bsr.w     $0001099A
[00010928] 41ef 0002                 lea.l     2(a7),a0
[0001092c] 6100 006c                 bsr.w     $0001099A
[00010930] 41eb ffec                 lea.l     -20(a3),a0
[00010934] 6100 0064                 bsr.w     $0001099A
[00010938] 41eb ffee                 lea.l     -18(a3),a0
[0001093c] 6100 005c                 bsr.w     $0001099A
[00010940] 302b fff0                 move.w    -16(a3),d0
[00010944] 670c                      beq.s     $00010952
[00010946] 7040                      moveq.l   #64,d0
[00010948] 6100 0326                 bsr       $00010C70
[0001094c] 426b 0014                 clr.w     20(a3)
[00010950] 600c                      bra.s     $0001095E
[00010952] 4200                      clr.b     d0
[00010954] 6100 031a                 bsr       $00010C70
[00010958] 377c 0004 0014            move.w    #$0004,20(a3)
[0001095e] 1005                      move.b    d5,d0
[00010960] 6100 030e                 bsr       $00010C70
[00010964] 4240                      clr.w     d0
[00010966] 3740 000e                 move.w    d0,14(a3)
[0001096a] 3740 000c                 move.w    d0,12(a3)
[0001096e] 7001                      moveq.l   #1,d0
[00010970] d045                      add.w     d5,d0
[00010972] 6100 003c                 bsr.w     $000109B0
[00010976] 4200                      clr.b     d0
[00010978] 6100 02f6                 bsr       $00010C70
[0001097c] 703b                      moveq.l   #59,d0
[0001097e] 6100 02f0                 bsr       $00010C70
[00010982] 302b ffe6                 move.w    -26(a3),d0
[00010986] 6f04                      ble.s     $0001098C
[00010988] 6100 02fe                 bsr       $00010C88
[0001098c] 302b ffe0                 move.w    -32(a3),d0
[00010990] 4fef 000a                 lea.l     10(a7),a7
[00010994] 4cdf 3cf8                 movem.l   (a7)+,d3-d7/a2-a5
[00010998] 4e75                      rts
[0001099a] 2f0a                      move.l    a2,-(a7)
[0001099c] 2448                      movea.l   a0,a2
[0001099e] 102a 0001                 move.b    1(a2),d0
[000109a2] 6100 02cc                 bsr       $00010C70
[000109a6] 1012                      move.b    (a2),d0
[000109a8] 6100 02c6                 bsr       $00010C70
[000109ac] 245f                      movea.l   (a7)+,a2
[000109ae] 4e75                      rts
[000109b0] 48e7 1f30                 movem.l   d3-d7/a2-a3,-(a7)
[000109b4] 47f9 0000 0dae            lea.l     $00000DAE,a3
[000109ba] 3740 001a                 move.w    d0,26(a3)
[000109be] 426b 0018                 clr.w     24(a3)
[000109c2] 7201                      moveq.l   #1,d1
[000109c4] 342b 001a                 move.w    26(a3),d2
[000109c8] 3742 0012                 move.w    d2,18(a3)
[000109cc] e569                      lsl.w     d2,d1
[000109ce] 5341                      subq.w    #1,d1
[000109d0] 3741 0014                 move.w    d1,20(a3)
[000109d4] 7401                      moveq.l   #1,d2
[000109d6] 72ff                      moveq.l   #-1,d1
[000109d8] d200                      add.b     d0,d1
[000109da] e36a                      lsl.w     d1,d2
[000109dc] 3742 001c                 move.w    d2,28(a3)
[000109e0] 7001                      moveq.l   #1,d0
[000109e2] d042                      add.w     d2,d0
[000109e4] 3740 001e                 move.w    d0,30(a3)
[000109e8] 45eb 0016                 lea.l     22(a3),a2
[000109ec] 7002                      moveq.l   #2,d0
[000109ee] d06b 001c                 add.w     28(a3),d0
[000109f2] 3480                      move.w    d0,(a2)
[000109f4] 6100 0216                 bsr       $00010C0C
[000109f8] 6100 fd16                 bsr       $00010710
[000109fc] 6100 fd48                 bsr       $00010746
[00010a00] 3600                      move.w    d0,d3
[00010a02] 6100 01d6                 bsr       $00010BDA
[00010a06] 426b 0024                 clr.w     36(a3)
[00010a0a] 302b 001c                 move.w    28(a3),d0
[00010a0e] 6100 00d0                 bsr       $00010AE0
[00010a12] 6000 00a8                 bra       $00010ABC
[00010a16] 0c6b ffff ffdc            cmpi.w    #$FFFF,-36(a3)
[00010a1c] 6700 00aa                 beq       $00010AC8
[00010a20] 3a04                      move.w    d4,d5
[00010a22] 48c5                      ext.l     d5
[00010a24] 700c                      moveq.l   #12,d0
[00010a26] e1ad                      lsl.l     d0,d5
[00010a28] 3203                      move.w    d3,d1
[00010a2a] 48c1                      ext.l     d1
[00010a2c] da81                      add.l     d1,d5
[00010a2e] 3c04                      move.w    d4,d6
[00010a30] e94e                      lsl.w     #4,d6
[00010a32] b746                      eor.w     d3,d6
[00010a34] 3406                      move.w    d6,d2
[00010a36] 48c2                      ext.l     d2
[00010a38] e58a                      lsl.l     #2,d2
[00010a3a] 2053                      movea.l   (a3),a0
[00010a3c] bab0 2800                 cmp.l     0(a0,d2.l),d5
[00010a40] 6728                      beq.s     $00010A6A
[00010a42] 2030 2800                 move.l    0(a0,d2.l),d0
[00010a46] 6b40                      bmi.s     $00010A88
[00010a48] 3e3c 138b                 move.w    #$138B,d7
[00010a4c] 9e46                      sub.w     d6,d7
[00010a4e] 4a46                      tst.w     d6
[00010a50] 6602                      bne.s     $00010A54
[00010a52] 7e01                      moveq.l   #1,d7
[00010a54] 9c47                      sub.w     d7,d6
[00010a56] 6a04                      bpl.s     $00010A5C
[00010a58] dc7c 138b                 add.w     #$138B,d6
[00010a5c] 3006                      move.w    d6,d0
[00010a5e] 48c0                      ext.l     d0
[00010a60] e588                      lsl.l     #2,d0
[00010a62] 2053                      movea.l   (a3),a0
[00010a64] bab0 0800                 cmp.l     0(a0,d0.l),d5
[00010a68] 6610                      bne.s     $00010A7A
[00010a6a] 3006                      move.w    d6,d0
[00010a6c] 48c0                      ext.l     d0
[00010a6e] d080                      add.l     d0,d0
[00010a70] 206b 0004                 movea.l   4(a3),a0
[00010a74] 3630 0800                 move.w    0(a0,d0.l),d3
[00010a78] 6042                      bra.s     $00010ABC
[00010a7a] 3006                      move.w    d6,d0
[00010a7c] 48c0                      ext.l     d0
[00010a7e] e588                      lsl.l     #2,d0
[00010a80] 2053                      movea.l   (a3),a0
[00010a82] 2230 0800                 move.l    0(a0,d0.l),d1
[00010a86] 6ecc                      bgt.s     $00010A54
[00010a88] 3003                      move.w    d3,d0
[00010a8a] 6100 0054                 bsr.w     $00010AE0
[00010a8e] 3604                      move.w    d4,d3
[00010a90] 3012                      move.w    (a2),d0
[00010a92] b079 0000 0d34            cmp.w     $00000D34,d0
[00010a98] 6c1e                      bge.s     $00010AB8
[00010a9a] 3206                      move.w    d6,d1
[00010a9c] 48c1                      ext.l     d1
[00010a9e] d281                      add.l     d1,d1
[00010aa0] 206b 0004                 movea.l   4(a3),a0
[00010aa4] 3180 1800                 move.w    d0,0(a0,d1.l)
[00010aa8] 5252                      addq.w    #1,(a2)
[00010aaa] 3406                      move.w    d6,d2
[00010aac] 48c2                      ext.l     d2
[00010aae] e58a                      lsl.l     #2,d2
[00010ab0] 2053                      movea.l   (a3),a0
[00010ab2] 2185 2800                 move.l    d5,0(a0,d2.l)
[00010ab6] 6004                      bra.s     $00010ABC
[00010ab8] 6100 00fa                 bsr       $00010BB4
[00010abc] 6100 fc88                 bsr       $00010746
[00010ac0] 3800                      move.w    d0,d4
[00010ac2] 5240                      addq.w    #1,d0
[00010ac4] 6600 ff50                 bne       $00010A16
[00010ac8] 3003                      move.w    d3,d0
[00010aca] 6100 0014                 bsr.w     $00010AE0
[00010ace] 302b 001e                 move.w    30(a3),d0
[00010ad2] 6100 000c                 bsr.w     $00010AE0
[00010ad6] 536b ffe2                 subq.w    #1,-30(a3)
[00010ada] 4cdf 0cf8                 movem.l   (a7)+,d3-d7/a2-a3
[00010ade] 4e75                      rts
[00010ae0] 48e7 1030                 movem.l   d3/a2-a3,-(a7)
[00010ae4] 3600                      move.w    d0,d3
[00010ae6] 45f9 0000 0dd2            lea.l     $00000DD2,a2
[00010aec] 47f9 0000 0dce            lea.l     $00000DCE,a3
[00010af2] 3012                      move.w    (a2),d0
[00010af4] 6f1c                      ble.s     $00010B12
[00010af6] e548                      lsl.w     #2,d0
[00010af8] 41f9 0000 0d36            lea.l     $00000D36,a0
[00010afe] 2230 0000                 move.l    0(a0,d0.w),d1
[00010b02] c393                      and.l     d1,(a3)
[00010b04] 3403                      move.w    d3,d2
[00010b06] 48c2                      ext.l     d2
[00010b08] 102a 0001                 move.b    1(a2),d0
[00010b0c] e1aa                      lsl.l     d0,d2
[00010b0e] 8593                      or.l      d2,(a3)
[00010b10] 6006                      bra.s     $00010B18
[00010b12] 3003                      move.w    d3,d0
[00010b14] 48c0                      ext.l     d0
[00010b16] 2680                      move.l    d0,(a3)
[00010b18] 302b fff2                 move.w    -14(a3),d0
[00010b1c] d152                      add.w     d0,(a2)
[00010b1e] 6014                      bra.s     $00010B34
[00010b20] 302b 0002                 move.w    2(a3),d0
[00010b24] c07c 00ff                 and.w     #$00FF,d0
[00010b28] 6100 00f4                 bsr       $00010C1E
[00010b2c] 2013                      move.l    (a3),d0
[00010b2e] e088                      lsr.l     #8,d0
[00010b30] 2680                      move.l    d0,(a3)
[00010b32] 5152                      subq.w    #8,(a2)
[00010b34] 0c52 0008                 cmpi.w    #$0008,(a2)
[00010b38] 6ce6                      bge.s     $00010B20
[00010b3a] 302b fff8                 move.w    -8(a3),d0
[00010b3e] 6718                      beq.s     $00010B58
[00010b40] 7201                      moveq.l   #1,d1
[00010b42] 342b fffa                 move.w    -6(a3),d2
[00010b46] 3742 fff2                 move.w    d2,-14(a3)
[00010b4a] e569                      lsl.w     d2,d1
[00010b4c] 5341                      subq.w    #1,d1
[00010b4e] 3741 fff4                 move.w    d1,-12(a3)
[00010b52] 426b fff8                 clr.w     -8(a3)
[00010b56] 602c                      bra.s     $00010B84
[00010b58] 302b fff6                 move.w    -10(a3),d0
[00010b5c] b06b fff4                 cmp.w     -12(a3),d0
[00010b60] 6f22                      ble.s     $00010B84
[00010b62] 526b fff2                 addq.w    #1,-14(a3)
[00010b66] 0c6b 000c fff2            cmpi.w    #$000C,-14(a3)
[00010b6c] 6608                      bne.s     $00010B76
[00010b6e] 3039 0000 0d34            move.w    $00000D34,d0
[00010b74] 600a                      bra.s     $00010B80
[00010b76] 7001                      moveq.l   #1,d0
[00010b78] 122b fff3                 move.b    -13(a3),d1
[00010b7c] e368                      lsl.w     d1,d0
[00010b7e] 5340                      subq.w    #1,d0
[00010b80] 3740 fff4                 move.w    d0,-12(a3)
[00010b84] b66b fffe                 cmp.w     -2(a3),d3
[00010b88] 6624                      bne.s     $00010BAE
[00010b8a] 6014                      bra.s     $00010BA0
[00010b8c] 302b 0002                 move.w    2(a3),d0
[00010b90] c07c 00ff                 and.w     #$00FF,d0
[00010b94] 6100 0088                 bsr       $00010C1E
[00010b98] 2013                      move.l    (a3),d0
[00010b9a] e088                      lsr.l     #8,d0
[00010b9c] 2680                      move.l    d0,(a3)
[00010b9e] 5152                      subq.w    #8,(a2)
[00010ba0] 3012                      move.w    (a2),d0
[00010ba2] 6ee8                      bgt.s     $00010B8C
[00010ba4] 322b ffc4                 move.w    -60(a3),d1
[00010ba8] 6f04                      ble.s     $00010BAE
[00010baa] 6100 0096                 bsr       $00010C42
[00010bae] 4cdf 0c08                 movem.l   (a7)+,d3/a2-a3
[00010bb2] 4e75                      rts
[00010bb4] 6100 0024                 bsr.w     $00010BDA
[00010bb8] 7002                      moveq.l   #2,d0
[00010bba] d079 0000 0dca            add.w     $00000DCA,d0
[00010bc0] 33c0 0000 0dc4            move.w    d0,$00000DC4
[00010bc6] 33fc 0001 0000 0dc6       move.w    #$0001,$00000DC6
[00010bce] 3039 0000 0dca            move.w    $00000DCA,d0
[00010bd4] 6100 ff0a                 bsr       $00010AE0
[00010bd8] 4e75                      rts
[00010bda] 2079 0000 0dae            movea.l   $00000DAE,a0
[00010be0] 41e8 4e2c                 lea.l     20012(a0),a0
[00010be4] 70ff                      moveq.l   #-1,d0
[00010be6] 323c 1383                 move.w    #$1383,d1
[00010bea] 2100                      move.l    d0,-(a0)
[00010bec] 2100                      move.l    d0,-(a0)
[00010bee] 2100                      move.l    d0,-(a0)
[00010bf0] 2100                      move.l    d0,-(a0)
[00010bf2] 2100                      move.l    d0,-(a0)
[00010bf4] 2100                      move.l    d0,-(a0)
[00010bf6] 2100                      move.l    d0,-(a0)
[00010bf8] 2100                      move.l    d0,-(a0)
[00010bfa] 5141                      subq.w    #8,d1
[00010bfc] 6aec                      bpl.s     $00010BEA
[00010bfe] 5041                      addq.w    #8,d1
[00010c00] 6004                      bra.s     $00010C06
[00010c02] 2100                      move.l    d0,-(a0)
[00010c04] 5341                      subq.w    #1,d1
[00010c06] 4a41                      tst.w     d1
[00010c08] 6ef8                      bgt.s     $00010C02
[00010c0a] 4e75                      rts
[00010c0c] 41f9 0000 0d90            lea.l     $00000D90,a0
[00010c12] 3150 0004                 move.w    (a0),4(a0)
[00010c16] 5250                      addq.w    #1,(a0)
[00010c18] 4268 0002                 clr.w     2(a0)
[00010c1c] 4e75                      rts
[00010c1e] 41f9 0000 0d90            lea.l     $00000D90,a0
[00010c24] 3210                      move.w    (a0),d1
[00010c26] 2268 fffc                 movea.l   -4(a0),a1
[00010c2a] 1380 1000                 move.b    d0,0(a1,d1.w)
[00010c2e] 5250                      addq.w    #1,(a0)
[00010c30] 5268 0002                 addq.w    #1,2(a0)
[00010c34] 0c68 00fe 0002            cmpi.w    #$00FE,2(a0)
[00010c3a] 6d04                      blt.s     $00010C40
[00010c3c] 6100 0004                 bsr.w     $00010C42
[00010c40] 4e75                      rts
[00010c42] 2f0a                      move.l    a2,-(a7)
[00010c44] 45f9 0000 0d90            lea.l     $00000D90,a2
[00010c4a] 302a 0004                 move.w    4(a2),d0
[00010c4e] 206a fffc                 movea.l   -4(a2),a0
[00010c52] 11aa 0003 0000            move.b    3(a2),0(a0,d0.w)
[00010c58] 0c52 0f00                 cmpi.w    #$0F00,(a2)
[00010c5c] 6d04                      blt.s     $00010C62
[00010c5e] 6100 0028                 bsr.w     $00010C88
[00010c62] 3552 0004                 move.w    (a2),4(a2)
[00010c66] 5252                      addq.w    #1,(a2)
[00010c68] 426a 0002                 clr.w     2(a2)
[00010c6c] 245f                      movea.l   (a7)+,a2
[00010c6e] 4e75                      rts
[00010c70] 3239 0000 0d90            move.w    $00000D90,d1
[00010c76] 2079 0000 0d8c            movea.l   $00000D8C,a0
[00010c7c] 1180 1000                 move.b    d0,0(a0,d1.w)
[00010c80] 5279 0000 0d90            addq.w    #1,$00000D90
[00010c86] 4e75                      rts
[00010c88] 2f0a                      move.l    a2,-(a7)
[00010c8a] 45f9 0000 0d90            lea.l     $00000D90,a2
[00010c90] 302a fffa                 move.w    -6(a2),d0
[00010c94] 661c                      bne.s     $00010CB2
[00010c96] 3212                      move.w    (a2),d1
[00010c98] 48c1                      ext.l     d1
[00010c9a] 2f01                      move.l    d1,-(a7)
[00010c9c] 206a fffc                 movea.l   -4(a2),a0
[00010ca0] 302a fff8                 move.w    -8(a2),d0
[00010ca4] 6100 003a                 bsr.w     $00010CE0
[00010ca8] b09f                      cmp.l     (a7)+,d0
[00010caa] 6706                      beq.s     $00010CB2
[00010cac] 357c ffff fffa            move.w    #$FFFF,-6(a2)
[00010cb2] 4252                      clr.w     (a2)
[00010cb4] 245f                      movea.l   (a7)+,a2
[00010cb6] 4e75                      rts
[00010cb8] 2400                      move.l    d0,d2
[00010cba] 4842                      swap      d2
[00010cbc] 4a42                      tst.w     d2
[00010cbe] 6616                      bne.s     $00010CD6
[00010cc0] 2401                      move.l    d1,d2
[00010cc2] 4842                      swap      d2
[00010cc4] 4a42                      tst.w     d2
[00010cc6] 6604                      bne.s     $00010CCC
[00010cc8] c0c1                      mulu.w    d1,d0
[00010cca] 4e75                      rts
[00010ccc] c4c0                      mulu.w    d0,d2
[00010cce] 4842                      swap      d2
[00010cd0] c0c1                      mulu.w    d1,d0
[00010cd2] d082                      add.l     d2,d0
[00010cd4] 4e75                      rts
[00010cd6] c4c1                      mulu.w    d1,d2
[00010cd8] 4842                      swap      d2
[00010cda] c0c1                      mulu.w    d1,d0
[00010cdc] d082                      add.l     d2,d0
[00010cde] 4e75                      rts
[00010ce0] 48e7 c0a0                 movem.l   d0-d1/a0/a2,-(a7)
[00010ce4] 3ebc 0040                 move.w    #$0040,(a7)
[00010ce8] 4e41                      trap      #1
[00010cea] 4fef 000c                 lea.l     12(a7),a7
[00010cee] 245f                      movea.l   (a7)+,a2
[00010cf0] 4e75                      rts
[00010cf2] 0808 0402                 btst      #1026,a0
[00010cf6] 0104                      btst      d0,d4
[00010cf8] 0201 ffff                 andi.b    #$FF,d1
[00010cfc] 1000                      move.b    d0,d0
[00010cfe] 0000 0000                 ori.b     #$00,d0
[00010d02] 0000 0001                 ori.b     #$01,d0
[00010d06] 0000 0003                 ori.b     #$03,d0
[00010d0a] 0000 0007                 ori.b     #$07,d0
[00010d0e] 0000 000f                 ori.b     #$0F,d0
[00010d12] 0000 001f                 ori.b     #$1F,d0
[00010d16] 0000 003f                 ori.b     #$3F,d0
[00010d1a] 0000 007f                 ori.b     #$7F,d0
[00010d1e] 0000 00ff                 ori.b     #$FF,d0
[00010d22] 0000 01ff                 ori.b     #$FF,d0
[00010d26] 0000 03ff                 ori.b     #$FF,d0
[00010d2a] 0000 07ff                 ori.b     #$FF,d0
[00010d2e] 0000 0fff                 ori.b     #$FF,d0
[00010d32] 0000 1fff                 ori.b     #$FF,d0
[00010d36] 0000 3fff                 ori.b     #$FF,d0
[00010d3a] 0000 7fff                 ori.b     #$FF,d0
[00010d3e] 0000 ffff                 ori.b     #$FF,d0
[00010d42] 4749                      lea.l     (b1),b3 ; apollo only
[00010d44] 4638 3761                 not.b     ($00003761).w
[00010d48] 0047 4946                 ori.w     #$4946,d7
[00010d4c] 3839 6100 0000            move.w    $61000000,d4
[00010d52] 0000 0000                 ori.b     #$00,d0
[00010d56] 0000 0000                 ori.b     #$00,d0
[00010d5a] 0000 0000                 ori.b     #$00,d0
[00010d5e] 0000 0000                 ori.b     #$00,d0
[00010d62] 0000 0000                 ori.b     #$00,d0
[00010d66] 0000 0000                 ori.b     #$00,d0
[00010d6a] 0000 0000                 ori.b     #$00,d0
[00010d6e] 0000 0000                 ori.b     #$00,d0
[00010d72] 0000 0000                 ori.b     #$00,d0
[00010d76] 0000 0000                 ori.b     #$00,d0
[00010d7a] 0000 0000                 ori.b     #$00,d0
[00010d7e] 0000 0000                 ori.b     #$00,d0
[00010d82] 0000 0000                 ori.b     #$00,d0
[00010d86] 0000 0000                 ori.b     #$00,d0
[00010d8a] 0000 0000                 ori.b     #$00,d0
[00010d8e] 0000 0000                 ori.b     #$00,d0
[00010d92] 0000 0000                 ori.b     #$00,d0
[00010d96] 0000 0000                 ori.b     #$00,d0
[00010d9a] 0000 0000                 ori.b     #$00,d0
[00010d9e] 06d6 7636                 callm     #$7636,(a6) ; 68020 only
[00010da2] 105e                      movea.l   (a6)+,b0 ; apollo only
[00010da4] 2e08                      move.l    a0,d7
[00010da6] 5606                      addq.b    #3,d6
[00010da8] 0e06 0e06                 and.b     d0,d6 ; apollo only
[00010dac] 0806 0138                 btst      #312,d6
[00010db0] de54                      add.w     (a4),d7
[00010db2] 060c 764c                 addi.b    #$4C,a4 ; apollo only
[00010db6] 0608 060c                 addi.b    #$0C,a0 ; apollo only
[00010dba] 3212                      move.w    (a2),d1
[00010dbc] 262c 060a                 move.l    1546(a4),d3
[00010dc0] 0a00 0000                 eori.b    #$00,d0
