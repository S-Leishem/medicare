#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <Preferences.h>
#include <Wire.h>
#include <time.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP32Servo.h>

void mbDigitalWrite(uint8_t pin, uint8_t value)
{
      digitalWrite(pin, value);
}

int mbDigitalRead(uint8_t pin)
{
  int v = digitalRead(pin);
      return v;
}


#define MB_JUNK_0000 8791

#define MB_JUNK_0001 (92 + 62)
#define MB_JUNK_0002   293   
#define MB_JUNK_0003 ((15) * (3))

#define MB_JUNK_0004 6693
#define MB_JUNK_0005 (11 + 20)
#define MB_JUNK_0006   288   

#define MB_JUNK_0007 ((18) * (11))

#define MB_JUNK_0008 1619
#define MB_JUNK_0009 (22 + 41)
#define MB_JUNK_0010   204   
#define MB_JUNK_0011 ((12) * (14))
#define MB_JUNK_0012 9767
#define MB_JUNK_0013 (89 + 98)

#define MB_JUNK_0014   413   
#define MB_JUNK_0015 ((15) * (11))
#define MB_JUNK_0016 9331

#define MB_JUNK_0017 (18 + 34)
#define MB_JUNK_0018   391   
#define MB_JUNK_0019 ((11) * (5))
#define MB_JUNK_0020 8766
#define MB_JUNK_0021 (22 + 15)

#define MB_JUNK_0022   214   

#define MB_JUNK_0023 ((14) * (12))
#define MB_JUNK_0024 5726
#define MB_JUNK_0025 (15 + 87)

#define MB_JUNK_0026   72   
#define MB_JUNK_0027 ((10) * (19))

#define MB_JUNK_0028 2035
#define MB_JUNK_0029 (85 + 72)

#define MB_JUNK_0030   126   
#define MB_JUNK_0031 ((1) * (3))
#define MB_JUNK_0032 3614
#define MB_JUNK_0033 (80 + 80)

#define MB_JUNK_0034   54   

#define MB_JUNK_0035 ((18) * (7))
#define MB_JUNK_0036 2817
#define MB_JUNK_0037 (18 + 1)

#define MB_JUNK_0038   27   
#define MB_JUNK_0039 ((18) * (4))
#define MB_JUNK_0040 509
#define MB_JUNK_0041 (58 + 73)
#define MB_JUNK_0042   108   

#define MB_JUNK_0043 ((14) * (20))
#define MB_JUNK_0044 8251
#define MB_JUNK_0045 (82 + 57)
#define MB_JUNK_0046   294   
#define MB_JUNK_0047 ((4) * (19))
#define MB_JUNK_0048 9485
#define MB_JUNK_0049 (49 + 23)
#define MB_JUNK_0050   188   
#define MB_JUNK_0051 ((8) * (18))
#define MB_JUNK_0052 5000

#define MB_JUNK_0053 (85 + 3)
#define MB_JUNK_0054   331   
#define MB_JUNK_0055 ((18) * (7))

#define MB_JUNK_0056 37

#define MB_JUNK_0057 (36 + 13)

#define MB_JUNK_0058   112   
#define MB_JUNK_0059 ((11) * (16))
#define MB_JUNK_0060 4003
#define MB_JUNK_0061 (63 + 93)
#define MB_JUNK_0062   125   
#define MB_JUNK_0063 ((15) * (8))
#define MB_JUNK_0064 6543
#define MB_JUNK_0065 (67 + 43)
#define MB_JUNK_0066   134   
#define MB_JUNK_0067 ((15) * (4))
#define MB_JUNK_0068 6183

#define MB_JUNK_0069 (61 + 42)
#define MB_JUNK_0070   388   
#define MB_JUNK_0071 ((3) * (5))
#define MB_JUNK_0072 2724

#define MB_JUNK_0073 (43 + 3)

#define MB_JUNK_0074   190   
#define MB_JUNK_0075 ((12) * (2))
#define MB_JUNK_0076 7728
#define MB_JUNK_0077 (51 + 19)
#define MB_JUNK_0078   132   
#define MB_JUNK_0079 ((10) * (13))
#define MB_JUNK_0080 5278
#define MB_JUNK_0081 (80 + 29)

#define MB_JUNK_0082   387   
#define MB_JUNK_0083 ((18) * (15))
#define MB_JUNK_0084 3630
#define MB_JUNK_0085 (28 + 97)
#define MB_JUNK_0086   477   
#define MB_JUNK_0087 ((20) * (5))
#define MB_JUNK_0088 9828
#define MB_JUNK_0089 (38 + 17)

#define MB_JUNK_0090   209   

#define MB_JUNK_0091 ((9) * (7))
#define MB_JUNK_0092 710
#define MB_JUNK_0093 (68 + 92)
#define MB_JUNK_0094   254   
#define MB_JUNK_0095 ((13) * (20))
#define MB_JUNK_0096 3784
#define MB_JUNK_0097 (55 + 89)
#define MB_JUNK_0098   212   
#define MB_JUNK_0099 ((8) * (16))
#define MB_JUNK_0100 2302
#define MB_JUNK_0101 (33 + 44)
#define MB_JUNK_0102   7   
#define MB_JUNK_0103 ((4) * (3))
#define MB_JUNK_0104 5906

#define MB_JUNK_0105 (4 + 73)
#define MB_JUNK_0106   391   
#define MB_JUNK_0107 ((3) * (12))
#define MB_JUNK_0108 7963
#define MB_JUNK_0109 (46 + 42)
#define MB_JUNK_0110   80   

#define MB_JUNK_0111 ((15) * (18))
#define MB_JUNK_0112 5269

#define MB_JUNK_0113 (28 + 36)
#define MB_JUNK_0114   410   
#define MB_JUNK_0115 ((11) * (10))

#define MB_JUNK_0116 3768

#define MB_JUNK_0117 (15 + 48)
#define MB_JUNK_0118   433   
#define MB_JUNK_0119 ((15) * (18))
#define MB_JUNK_0120 1642

#define MB_JUNK_0121 (21 + 80)
#define MB_JUNK_0122   459   
#define MB_JUNK_0123 ((6) * (3))
#define MB_JUNK_0124 9133
#define MB_JUNK_0125 (65 + 14)
#define MB_JUNK_0126   403   
#define MB_JUNK_0127 ((12) * (8))
#define MB_JUNK_0128 2904

#define MB_JUNK_0129 (66 + 78)
#define MB_JUNK_0130   258   
#define MB_JUNK_0131 ((5) * (5))
#define MB_JUNK_0132 4431
#define MB_JUNK_0133 (96 + 6)
#define MB_JUNK_0134   282   
#define MB_JUNK_0135 ((1) * (12))
#define MB_JUNK_0136 4545
#define MB_JUNK_0137 (99 + 19)
#define MB_JUNK_0138   443   

#define MB_JUNK_0139 ((9) * (11))
#define MB_JUNK_0140 9515
#define MB_JUNK_0141 (93 + 28)
#define MB_JUNK_0142   154   
#define MB_JUNK_0143 ((6) * (11))
#define MB_JUNK_0144 5699
#define MB_JUNK_0145 (27 + 98)
#define MB_JUNK_0146   283   
#define MB_JUNK_0147 ((12) * (10))

#define MB_JUNK_0148 6498
#define MB_JUNK_0149 (46 + 29)
#define MB_JUNK_0150   300   
#define MB_JUNK_0151 ((1) * (20))

#define MB_JUNK_0152 9228
#define MB_JUNK_0153 (14 + 67)
#define MB_JUNK_0154   91   
#define MB_JUNK_0155 ((17) * (2))
#define MB_JUNK_0156 109
#define MB_JUNK_0157 (40 + 55)
#define MB_JUNK_0158   101   
#define MB_JUNK_0159 ((12) * (1))
#define MB_JUNK_0160 4116
#define MB_JUNK_0161 (46 + 87)
#define MB_JUNK_0162   247   
#define MB_JUNK_0163 ((3) * (18))
#define MB_JUNK_0164 641

#define MB_JUNK_0165 (77 + 11)
#define MB_JUNK_0166   370   
#define MB_JUNK_0167 ((20) * (10))
#define MB_JUNK_0168 7350
#define MB_JUNK_0169 (44 + 15)
#define MB_JUNK_0170   462   

#define MB_JUNK_0171 ((1) * (7))
#define MB_JUNK_0172 8038

#define MB_JUNK_0173 (98 + 85)
#define MB_JUNK_0174   224   
#define MB_JUNK_0175 ((3) * (16))
#define MB_JUNK_0176 5047
#define MB_JUNK_0177 (21 + 25)
#define MB_JUNK_0178   406   
#define MB_JUNK_0179 ((10) * (14))
#define MB_JUNK_0180 2381
#define MB_JUNK_0181 (73 + 25)
#define MB_JUNK_0182   386   
#define MB_JUNK_0183 ((17) * (13))

#define MB_JUNK_0184 827
#define MB_JUNK_0185 (46 + 56)

#define MB_JUNK_0186   353   
#define MB_JUNK_0187 ((8) * (7))
#define MB_JUNK_0188 6402
#define MB_JUNK_0189 (26 + 97)
#define MB_JUNK_0190   461   
#define MB_JUNK_0191 ((19) * (1))
#define MB_JUNK_0192 636
#define MB_JUNK_0193 (23 + 41)
#define MB_JUNK_0194   404   

#define MB_JUNK_0195 ((17) * (14))
#define MB_JUNK_0196 5789
#define MB_JUNK_0197 (14 + 80)
#define MB_JUNK_0198   469   

#define MB_JUNK_0199 ((5) * (1))
#define MB_JUNK_0200 5435
#define MB_JUNK_0201 (89 + 26)
#define MB_JUNK_0202   235   
#define MB_JUNK_0203 ((2) * (18))
#define MB_JUNK_0204 6038
#define MB_JUNK_0205 (63 + 96)
#define MB_JUNK_0206   15   
#define MB_JUNK_0207 ((9) * (18))
#define MB_JUNK_0208 6445
#define MB_JUNK_0209 (8 + 72)
#define MB_JUNK_0210   277   
#define MB_JUNK_0211 ((16) * (2))
#define MB_JUNK_0212 2298
#define MB_JUNK_0213 (62 + 93)
#define MB_JUNK_0214   482   
#define MB_JUNK_0215 ((5) * (1))
#define MB_JUNK_0216 3488
#define MB_JUNK_0217 (73 + 31)
#define MB_JUNK_0218   66   
#define MB_JUNK_0219 ((10) * (10))
#define MB_JUNK_0220 1223
#define MB_JUNK_0221 (57 + 30)
#define MB_JUNK_0222   129   

#define MB_JUNK_0223 ((18) * (2))
#define MB_JUNK_0224 4379
#define MB_JUNK_0225 (66 + 25)
#define MB_JUNK_0226   98   
#define MB_JUNK_0227 ((2) * (20))
#define MB_JUNK_0228 7348
#define MB_JUNK_0229 (53 + 26)

#define MB_JUNK_0230   466   

#define MB_JUNK_0231 ((1) * (17))
#define MB_JUNK_0232 1487
#define MB_JUNK_0233 (34 + 2)

#define MB_JUNK_0234   417   

#define MB_JUNK_0235 ((18) * (15))
#define MB_JUNK_0236 4889
#define MB_JUNK_0237 (36 + 43)
#define MB_JUNK_0238   183   
#define MB_JUNK_0239 ((13) * (19))
#define MB_JUNK_0240 1995
#define MB_JUNK_0241 (45 + 85)
#define MB_JUNK_0242   437   
#define MB_JUNK_0243 ((17) * (19))
#define MB_JUNK_0244 8785
#define MB_JUNK_0245 (60 + 70)
#define MB_JUNK_0246   426   
#define MB_JUNK_0247 ((10) * (8))
#define MB_JUNK_0248 8985

#define MB_JUNK_0249 (26 + 32)
#define MB_JUNK_0250   390   
#define MB_JUNK_0251 ((13) * (16))
#define MB_JUNK_0252 7717
#define MB_JUNK_0253 (43 + 35)
#define MB_JUNK_0254   31   
#define MB_JUNK_0255 ((3) * (11))
#define MB_JUNK_0256 1138
#define MB_JUNK_0257 (12 + 18)
#define MB_JUNK_0258   215   
#define MB_JUNK_0259 ((14) * (19))
#define MB_JUNK_0260 6228
#define MB_JUNK_0261 (12 + 89)
#define MB_JUNK_0262   16   
#define MB_JUNK_0263 ((17) * (17))
#define MB_JUNK_0264 2710
#define MB_JUNK_0265 (82 + 24)

#define MB_JUNK_0266   113   

#define MB_JUNK_0267 ((3) * (19))
#define MB_JUNK_0268 7371

#define MB_JUNK_0269 (43 + 94)

#define MB_JUNK_0270   123   
#define MB_JUNK_0271 ((16) * (18))
#define MB_JUNK_0272 9057
#define MB_JUNK_0273 (14 + 5)
#define MB_JUNK_0274   174   
#define MB_JUNK_0275 ((1) * (4))
#define MB_JUNK_0276 6001
#define MB_JUNK_0277 (89 + 61)
#define MB_JUNK_0278   58   
#define MB_JUNK_0279 ((4) * (2))
#define MB_JUNK_0280 3517
#define MB_JUNK_0281 (32 + 87)
#define MB_JUNK_0282   265   
#define MB_JUNK_0283 ((20) * (12))
#define MB_JUNK_0284 9844
#define MB_JUNK_0285 (34 + 6)
#define MB_JUNK_0286   482   
#define MB_JUNK_0287 ((9) * (19))
#define MB_JUNK_0288 7599
#define MB_JUNK_0289 (51 + 28)
#define MB_JUNK_0290   291   
#define MB_JUNK_0291 ((19) * (12))
#define MB_JUNK_0292 3057

#define MB_JUNK_0293 (62 + 48)

#define MB_JUNK_0294   469   

#define MB_JUNK_0295 ((9) * (3))
#define MB_JUNK_0296 424
#define MB_JUNK_0297 (3 + 3)
#define MB_JUNK_0298   158   
#define MB_JUNK_0299 ((8) * (14))
#define MB_JUNK_0300 6111
#define MB_JUNK_0301 (53 + 16)
#define MB_JUNK_0302   336   

#define MB_JUNK_0303 ((10) * (10))
#define MB_JUNK_0304 9715
#define MB_JUNK_0305 (77 + 28)
#define MB_JUNK_0306   169   
#define MB_JUNK_0307 ((17) * (9))
#define MB_JUNK_0308 4663
#define MB_JUNK_0309 (90 + 57)
#define MB_JUNK_0310   37   
#define MB_JUNK_0311 ((6) * (20))
#define MB_JUNK_0312 3983

#define MB_JUNK_0313 (62 + 20)
#define MB_JUNK_0314   205   
#define MB_JUNK_0315 ((14) * (19))

#define MB_JUNK_0316 2160
#define MB_JUNK_0317 (65 + 50)
#define MB_JUNK_0318   209   
#define MB_JUNK_0319 ((19) * (4))
#define MB_JUNK_0320 6821
#define MB_JUNK_0321 (65 + 41)
#define MB_JUNK_0322   454   
#define MB_JUNK_0323 ((18) * (12))
#define MB_JUNK_0324 3650
#define MB_JUNK_0325 (12 + 16)
#define MB_JUNK_0326   42   
#define MB_JUNK_0327 ((18) * (13))

#define MB_JUNK_0328 5219
#define MB_JUNK_0329 (3 + 89)
#define MB_JUNK_0330   432   
#define MB_JUNK_0331 ((20) * (12))
#define MB_JUNK_0332 7278

#define MB_JUNK_0333 (36 + 19)
#define MB_JUNK_0334   55   

#define MB_JUNK_0335 ((15) * (17))
#define MB_JUNK_0336 1250
#define MB_JUNK_0337 (56 + 87)
#define MB_JUNK_0338   63   
#define MB_JUNK_0339 ((15) * (9))
#define MB_JUNK_0340 8880

#define MB_JUNK_0341 (48 + 56)
#define MB_JUNK_0342   268   
#define MB_JUNK_0343 ((16) * (6))
#define MB_JUNK_0344 1101
#define MB_JUNK_0345 (15 + 91)
#define MB_JUNK_0346   298   
#define MB_JUNK_0347 ((12) * (11))
#define MB_JUNK_0348 5523
#define MB_JUNK_0349 (40 + 94)

#define MB_JUNK_0350   178   
#define MB_JUNK_0351 ((3) * (4))
#define MB_JUNK_0352 5104
#define MB_JUNK_0353 (99 + 52)
#define MB_JUNK_0354   353   
#define MB_JUNK_0355 ((6) * (1))
#define MB_JUNK_0356 9626
#define MB_JUNK_0357 (37 + 65)
#define MB_JUNK_0358   479   

#define MB_JUNK_0359 ((15) * (5))
#define MB_JUNK_0360 723
#define MB_JUNK_0361 (54 + 99)
#define MB_JUNK_0362   446   
#define MB_JUNK_0363 ((18) * (20))
#define MB_JUNK_0364 8727
#define MB_JUNK_0365 (22 + 7)
#define MB_JUNK_0366   444   
#define MB_JUNK_0367 ((13) * (18))

#define MB_JUNK_0368 6596
#define MB_JUNK_0369 (75 + 63)
#define MB_JUNK_0370   7   
#define MB_JUNK_0371 ((13) * (17))

#define MB_JUNK_0372 6192
#define MB_JUNK_0373 (59 + 68)
#define MB_JUNK_0374   235   
#define MB_JUNK_0375 ((9) * (19))
#define MB_JUNK_0376 7427
#define MB_JUNK_0377 (37 + 61)
#define MB_JUNK_0378   18   
#define MB_JUNK_0379 ((15) * (18))
#define MB_JUNK_0380 9754
#define MB_JUNK_0381 (28 + 79)
#define MB_JUNK_0382   158   
#define MB_JUNK_0383 ((15) * (18))
#define MB_JUNK_0384 3670
#define MB_JUNK_0385 (95 + 30)
#define MB_JUNK_0386   331   
#define MB_JUNK_0387 ((1) * (6))
#define MB_JUNK_0388 8621
#define MB_JUNK_0389 (4 + 47)
#define MB_JUNK_0390   262   

#define MB_JUNK_0391 ((12) * (18))

#define MB_JUNK_0392 5316

#define MB_JUNK_0393 (2 + 87)
#define MB_JUNK_0394   366   
#define MB_JUNK_0395 ((17) * (6))

#define MB_JUNK_0396 2080
#define MB_JUNK_0397 (87 + 19)
#define MB_JUNK_0398   12   
#define MB_JUNK_0399 ((6) * (17))
#define MB_JUNK_0400 6495
#define MB_JUNK_0401 (54 + 52)
#define MB_JUNK_0402   494   
#define MB_JUNK_0403 ((4) * (18))
#define MB_JUNK_0404 2920
#define MB_JUNK_0405 (73 + 31)
#define MB_JUNK_0406   195   
#define MB_JUNK_0407 ((7) * (17))

#define MB_JUNK_0408 1747
#define MB_JUNK_0409 (4 + 17)
#define MB_JUNK_0410   114   
#define MB_JUNK_0411 ((19) * (4))
#define MB_JUNK_0412 8344
#define MB_JUNK_0413 (38 + 26)
#define MB_JUNK_0414   475   
#define MB_JUNK_0415 ((6) * (11))
#define MB_JUNK_0416 7182
#define MB_JUNK_0417 (34 + 12)
#define MB_JUNK_0418   310   

#define MB_JUNK_0419 ((15) * (10))

const uint8_t MB_TABLE_000[12] =
{
  4, 66, 2, 70,
    33, 145, 171, 159,
   83, 88, 145, 10
};
const uint8_t MB_TABLE_001[8] =
{
    187, 107, 224, 175,
     99, 181, 100, 183
};
const uint8_t MB_TABLE_002[16] =
{
  109, 243, 172, 143,
    136, 7, 189, 179,
      141, 82, 96, 90,
   210, 39, 112, 1
};
const uint8_t MB_TABLE_003[16] =
{
     17, 147, 41, 51,
     143, 154, 195, 107,
   155, 90, 162, 196,
     101, 197, 213, 11
};
const uint8_t MB_TABLE_004[16] =
{
      69, 252, 197, 197,
    11, 85, 54, 147,
  89, 186, 218, 223,
     186, 128, 139, 9
};
const uint8_t MB_TABLE_005[8] =
{
  149, 128, 64, 99,
    197, 143, 12, 234
};
const uint8_t MB_TABLE_006[16] =
{
    73, 215, 48, 151,
     85, 246, 165, 242,
     16, 1, 78, 138,
   89, 126, 61, 229
};
const uint8_t MB_TABLE_007[16] =
{
  210, 39, 26, 66,
    186, 102, 61, 26,
     65, 167, 220, 56,
     244, 143, 7, 65
};
const uint8_t MB_TABLE_008[16] =
{
  233, 105, 148, 189,
   149, 67, 77, 138,
   155, 101, 37, 221,
     118, 76, 36, 55
};
const uint8_t MB_TABLE_009[8] =
{
    173, 59, 178, 87,
   168, 82, 120, 181
};
const uint8_t MB_TABLE_010[12] =
{
   102, 225, 203, 161,
     15, 156, 165, 30,
  138, 131, 9, 211
};

const uint8_t MB_TABLE_011[16] =
{
      19, 96, 118, 154,
   169, 206, 8, 40,
     253, 231, 99, 137,
  201, 235, 173, 238
};
const uint8_t MB_TABLE_012[8] =
{
     225, 61, 216, 142,
   212, 129, 117, 169
};

const uint8_t MB_TABLE_013[12] =
{
   39, 116, 197, 81,
    201, 185, 9, 165,
   83, 165, 141, 71
};
const uint8_t MB_TABLE_014[16] =
{
      37, 7, 230, 29,
   36, 117, 101, 32,
   198, 199, 168, 154,
      135, 132, 170, 134
};
const uint8_t MB_TABLE_015[16] =
{
      50, 33, 183, 151,
   195, 5, 24, 163,
   192, 70, 191, 103,
     63, 31, 55, 159
};
const uint8_t MB_TABLE_016[12] =
{
      72, 66, 32, 18,
      201, 14, 255, 109,
      175, 57, 161, 225
};

const uint8_t MB_TABLE_017[12] =
{
    119, 242, 108, 242,
   229, 145, 131, 189,
  173, 42, 105, 75
};
const uint8_t MB_TABLE_018[8] =
{
    82, 85, 177, 201,
  155, 65, 157, 50
};
const uint8_t MB_TABLE_019[12] =
{
      125, 167, 99, 230,
     125, 185, 14, 90,
  150, 11, 152, 81
};

const uint8_t MB_TABLE_020[16] =
{
      80, 111, 84, 46,
    100, 122, 164, 243,
    236, 107, 99, 174,
      159, 26, 71, 190
};

const uint8_t MB_TABLE_021[12] =
{
      195, 158, 253, 128,
     229, 89, 105, 143,
  87, 120, 254, 24
};

const uint8_t MB_TABLE_022[12] =
{
  250, 215, 170, 129,
  1, 161, 25, 199,
     26, 169, 9, 58
};
const uint8_t MB_TABLE_023[8] =
{
   249, 122, 235, 33,
   160, 222, 101, 135
};
const uint8_t MB_TABLE_024[8] =
{
   16, 146, 193, 176,
      58, 244, 133, 55
};
const uint8_t MB_TABLE_025[16] =
{
    54, 119, 188, 99,
      111, 150, 93, 2,
     24, 121, 155, 250,
   97, 228, 128, 199
};
const uint8_t MB_TABLE_026[16] =
{
    87, 216, 21, 92,
  42, 21, 10, 219,
   181, 64, 57, 15,
    88, 213, 130, 177
};

const uint8_t MB_TABLE_027[16] =
{
  101, 214, 11, 251,
  182, 107, 75, 215,
      96, 238, 81, 128,
   188, 199, 213, 111
};

const uint8_t MB_TABLE_028[16] =
{
  198, 77, 249, 242,
   128, 236, 61, 86,
   132, 227, 216, 241,
      243, 239, 41, 8
};
const uint8_t MB_TABLE_029[12] =
{
  52, 233, 168, 137,
     92, 2, 74, 150,
    125, 62, 122, 130
};
const uint8_t MB_TABLE_030[12] =
{
   231, 23, 145, 159,
      16, 20, 218, 125,
      210, 186, 163, 196
};
const uint8_t MB_TABLE_031[16] =
{
  239, 201, 135, 242,
   153, 1, 104, 75,
    218, 191, 247, 39,
   37, 24, 174, 85
};

const uint8_t MB_TABLE_032[12] =
{
    83, 94, 173, 105,
    235, 197, 151, 236,
  18, 226, 23, 209
};
const uint8_t MB_TABLE_033[8] =
{
     202, 144, 74, 158,
      237, 109, 184, 173
};
const uint8_t MB_TABLE_034[16] =
{
  66, 133, 76, 240,
   243, 213, 65, 232,
      207, 129, 245, 86,
    27, 137, 73, 185
};
const uint8_t MB_TABLE_035[8] =
{
     39, 141, 219, 176,
    213, 254, 253, 115
};
const uint8_t MB_TABLE_036[8] =
{
      172, 60, 227, 62,
    239, 243, 254, 234
};
const uint8_t MB_TABLE_037[8] =
{
     40, 71, 79, 41,
      37, 71, 252, 212
};
const uint8_t MB_TABLE_038[12] =
{
     42, 169, 205, 222,
      150, 61, 144, 245,
     253, 102, 214, 251
};
const uint8_t MB_TABLE_039[16] =
{
   180, 52, 187, 46,
  244, 251, 3, 149,
     58, 112, 248, 51,
    212, 187, 125, 111
};

const uint8_t MB_TABLE_040[8] =
{
    31, 49, 201, 50,
  238, 47, 58, 246
};

const uint8_t MB_TABLE_041[12] =
{
      224, 167, 32, 58,
    63, 215, 249, 210,
  205, 95, 202, 201
};
const uint8_t MB_TABLE_042[12] =
{
    123, 171, 88, 217,
     111, 105, 212, 193,
  111, 16, 228, 19
};

const uint8_t MB_TABLE_043[12] =
{
    19, 59, 242, 84,
   175, 209, 4, 74,
    39, 146, 104, 68
};

const uint8_t MB_TABLE_044[16] =
{
      12, 58, 227, 2,
  19, 125, 10, 233,
      101, 189, 136, 30,
      161, 241, 212, 115
};

const uint8_t MB_TABLE_045[16] =
{
   167, 166, 71, 73,
   161, 198, 183, 55,
    49, 29, 213, 170,
     139, 204, 131, 177
};
const uint8_t MB_TABLE_046[8] =
{
    125, 47, 86, 108,
   244, 158, 20, 52
};
const uint8_t MB_TABLE_047[8] =
{
     97, 159, 123, 132,
     179, 86, 40, 6
};
const uint8_t MB_TABLE_048[8] =
{
      183, 202, 135, 53,
     77, 148, 237, 236
};
const uint8_t MB_TABLE_049[16] =
{
     24, 152, 51, 104,
    27, 139, 194, 244,
      215, 34, 8, 39,
  249, 189, 17, 38
};

const uint8_t MB_TABLE_050[12] =
{
   144, 187, 14, 28,
   9, 120, 34, 71,
  1, 148, 19, 140
};
const uint8_t MB_TABLE_051[16] =
{
     235, 243, 148, 242,
    248, 66, 154, 249,
  47, 218, 134, 214,
  48, 72, 101, 1
};
const uint8_t MB_TABLE_052[8] =
{
   243, 198, 143, 111,
   246, 237, 176, 255
};
const uint8_t MB_TABLE_053[16] =
{
   248, 246, 222, 178,
  28, 114, 102, 161,
     85, 95, 176, 121,
     229, 102, 211, 133
};
const uint8_t MB_TABLE_054[12] =
{
   186, 84, 160, 146,
    72, 196, 168, 214,
   112, 202, 105, 243
};

const uint8_t MB_TABLE_055[16] =
{
     70, 39, 254, 72,
   172, 152, 124, 240,
   77, 70, 70, 178,
     254, 23, 78, 0
};
const uint8_t MB_TABLE_056[16] =
{
     119, 7, 157, 180,
      175, 114, 179, 55,
      94, 231, 157, 214,
   117, 78, 245, 180
};
const uint8_t MB_TABLE_057[8] =
{
    76, 178, 222, 168,
      114, 54, 220, 184
};
const uint8_t MB_TABLE_058[12] =
{
    196, 20, 14, 239,
  79, 205, 93, 66,
      137, 140, 121, 130
};

const uint8_t MB_TABLE_059[16] =
{
      171, 101, 151, 208,
      54, 18, 43, 176,
  163, 59, 211, 89,
    156, 107, 163, 194
};

const uint8_t MB_TABLE_060[8] =
{
   182, 212, 59, 112,
  109, 152, 157, 253
};
const uint8_t MB_TABLE_061[8] =
{
    166, 44, 211, 34,
    14, 18, 134, 174
};

const uint8_t MB_TABLE_062[8] =
{
    76, 197, 50, 181,
    193, 174, 5, 118
};
const uint8_t MB_TABLE_063[8] =
{
    169, 178, 147, 84,
    149, 60, 10, 228
};
const uint8_t MB_TABLE_064[8] =
{
     29, 237, 160, 55,
      183, 101, 221, 197
};

const uint8_t MB_TABLE_065[8] =
{
     202, 146, 223, 148,
      171, 48, 183, 100
};
const uint8_t MB_TABLE_066[16] =
{
   34, 65, 98, 45,
   38, 139, 37, 216,
    41, 44, 155, 202,
     215, 201, 196, 47
};
const uint8_t MB_TABLE_067[12] =
{
  153, 238, 67, 17,
    102, 19, 82, 127,
      148, 12, 188, 10
};

const uint8_t MB_TABLE_068[12] =
{
      9, 162, 74, 183,
    214, 36, 209, 59,
     155, 21, 194, 167
};

const uint8_t MB_TABLE_069[16] =
{
  102, 224, 122, 139,
    144, 40, 233, 227,
  235, 102, 220, 96,
  90, 6, 16, 152
};
const uint8_t MB_TABLE_070[16] =
{
    53, 151, 208, 143,
  223, 119, 200, 175,
      224, 220, 91, 188,
   161, 39, 218, 50
};
const uint8_t MB_TABLE_071[12] =
{
     116, 46, 152, 250,
      117, 117, 138, 185,
   44, 79, 132, 203
};

const uint8_t MB_TABLE_072[16] =
{
   59, 235, 69, 23,
   109, 252, 95, 141,
      175, 193, 150, 182,
     45, 181, 88, 104
};
const uint8_t MB_TABLE_073[16] =
{
      74, 170, 137, 67,
  227, 91, 61, 194,
     11, 94, 180, 33,
  175, 67, 56, 59
};
const uint8_t MB_TABLE_074[8] =
{
     91, 245, 70, 77,
   106, 71, 198, 62
};

const uint8_t MB_TABLE_075[12] =
{
     224, 193, 217, 139,
    166, 13, 179, 248,
   229, 144, 119, 189
};
const uint8_t MB_TABLE_076[16] =
{
      90, 170, 34, 160,
     237, 162, 185, 36,
   199, 211, 17, 163,
  137, 241, 110, 32
};

const uint8_t MB_TABLE_077[12] =
{
   90, 184, 19, 8,
   230, 16, 1, 44,
   120, 74, 91, 14
};

const uint8_t MB_TABLE_078[8] =
{
  13, 1, 26, 82,
   222, 236, 1, 87
};
const uint8_t MB_TABLE_079[16] =
{
     220, 182, 46, 194,
  66, 211, 195, 67,
      219, 38, 30, 250,
    140, 241, 130, 54
};
const uint8_t MB_TABLE_080[8] =
{
    31, 83, 180, 157,
    5, 94, 48, 190
};

const uint8_t MB_TABLE_081[8] =
{
  10, 218, 191, 59,
      193, 30, 76, 46
};
const uint8_t MB_TABLE_082[12] =
{
    107, 184, 113, 82,
  172, 159, 103, 106,
    118, 128, 111, 204
};
const uint8_t MB_TABLE_083[8] =
{
   37, 54, 96, 137,
    138, 231, 131, 3
};
const uint8_t MB_TABLE_084[16] =
{
      48, 51, 68, 101,
     29, 40, 175, 104,
   226, 16, 245, 12,
  192, 162, 109, 116
};
const uint8_t MB_TABLE_085[8] =
{
    19, 45, 18, 213,
      26, 113, 54, 183
};
const uint8_t MB_TABLE_086[12] =
{
      224, 242, 160, 50,
  5, 112, 52, 1,
     151, 63, 74, 210
};
const uint8_t MB_TABLE_087[12] =
{
      13, 64, 134, 204,
  233, 59, 92, 179,
      244, 248, 203, 163
};
const uint8_t MB_TABLE_088[12] =
{
    237, 56, 69, 179,
    45, 46, 243, 167,
     19, 57, 162, 10
};
const uint8_t MB_TABLE_089[8] =
{
     231, 142, 110, 70,
     18, 50, 10, 196
};
const uint8_t MB_TABLE_090[8] =
{
    204, 22, 54, 112,
   76, 182, 200, 29
};
const uint8_t MB_TABLE_091[12] =
{
    9, 225, 100, 196,
    180, 204, 122, 216,
  226, 189, 114, 52
};
const uint8_t MB_TABLE_092[16] =
{
   201, 184, 191, 22,
  11, 210, 213, 183,
    156, 69, 128, 177,
      113, 35, 133, 180
};
const uint8_t MB_TABLE_093[16] =
{
     247, 177, 12, 158,
      127, 247, 76, 136,
     104, 56, 246, 53,
    158, 171, 83, 87
};
const uint8_t MB_TABLE_094[8] =
{
     129, 164, 39, 33,
  94, 151, 64, 125
};



     const char* WIFI_SSID = "Soubam";
const char* WIFI_PASSWORD = "Linlin@1";

const char* NTP_SERVER_1 = "pool.ntp.org";

const char* NTP_SERVER_2 = "time.nist.gov";


const long GMT_OFFSET_SECONDS = 19800;
const int DAYLIGHT_OFFSET_SECONDS = 0;

constexpr uint16_t WEB_SERVER_PORT = 5500;

constexpr uint8_t SERVO_PINS[3] = {18, 19, 23};
constexpr uint8_t LED_PINS[3] = {13, 14, 33};

constexpr uint8_t MEDICINE_BUZZER_PIN = 25;

constexpr uint8_t SOS_BUZZER_PIN = 26;


constexpr uint8_t RGB_RED_PIN = 32;
constexpr uint8_t RGB_GREEN_PIN = 15;
     constexpr uint8_t RGB_BLUE_PIN = 2;

constexpr uint8_t SOS_BUTTON_PIN = 27;
constexpr uint8_t IR_SENSOR_PIN = 34;

constexpr uint8_t OLED_SDA_PIN = 21;
 constexpr uint8_t OLED_SCL_PIN = 22;


constexpr uint8_t OLED_ADDRESS = 0x3C;

constexpr bool IR_ACTIVE_LOW = true;
constexpr bool SOS_BUTTON_ACTIVE_LOW = true;
constexpr bool RGB_COMMON_CATHODE = true;


constexpr int CLOSED_ANGLE = 0;
constexpr int OPEN_ANGLE = 180;
  constexpr uint16_t SERVO_STEP_INTERVAL_MS = 15;
constexpr uint8_t SERVO_STEP_DEGREES = 3;

constexpr uint16_t IR_DEBOUNCE_MS = 60;


constexpr uint16_t BUTTON_DEBOUNCE_MS = 40;


constexpr uint32_t SOS_LONG_PRESS_MS = 3000;



const char* NAMES[3] = {"Morning", "Afternoon", "Night"};

struct Schedule {
  bool enabled;
  uint8_t hour;
  uint8_t minute;
  int32_t lastFiredDay;
};



struct Compartment {
  Servo servo;
  bool ringing;

     int angle;
  int target;

  uint32_t lastStep;

  uint32_t ringStart;
};

Schedule schedules[3] = {
  {true, 8, 0, -1},
  {true, 13, 0, -1},
  {true, 20, 0, -1}
};

      Compartment compartments[3];

      WebServer server(WEB_SERVER_PORT);
Preferences prefs;
Adafruit_SSD1306 display(128, 64, &Wire, -1);

      bool displayOk = false;
bool networkStarted = false;
uint32_t lastWiFiAttempt = 0;

uint32_t lastDisplay = 0;
uint32_t lastDisplayCheck = 0;
int lastDrawnSecond = -1;
uint32_t lastScheduleCheck = 0;

uint32_t lastSerial = 0;


bool sosActive = false;
bool sosButtonPressed = false;
bool sosLongPressHandled = false;
uint32_t sosButtonDownAt = 0;


uint32_t lastSosButtonChange = 0;
uint32_t lastSosBlink = 0;
      bool sosBlinkState = false;


bool irStable = false;
bool irLastRaw = false;
      uint32_t irLastChange = 0;



const char PAGE[] PROGMEM = R"rawliteral(<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8"><meta name="viewport" content="width=device-width, initial-scale=1">
<title>MediBox | Settings</title>
<style>
:root{font-family:system-ui,-apple-system,Segoe UI,sans-serif;color:#183346;background:#eef5f7}*{box-sizing:border-box}body{margin:0}.wrap{max-width:940px;margin:auto;padding:28px 18px}header{display:flex;align-items:center;justify-content:space-between;gap:16px;flex-wrap:wrap;margin-bottom:22px}.brand{font-size:1.5rem;font-weight:800}.muted{color:#647786;font-size:.9rem}.badge{background:#e2f7ef;color:#126d52;padding:9px 13px;border-radius:40px;font-size:.85rem}.badge.off{background:#fde8ea;color:#b52732}.grid{display:grid;grid-template-columns:repeat(3,minmax(0,1fr));gap:16px}.card{background:white;border:1px solid #dce9ed;border-radius:18px;padding:22px;box-shadow:0 7px 24px #15374c0a}.card h2{font-size:1.1rem;margin:0 0 6px}.pill{font-size:.78rem;background:#e7f5f6;color:#16767a;border-radius:20px;padding:4px 9px;display:inline-block;margin-bottom:16px}label{display:block;font-weight:600;font-size:.88rem;margin:14px 0 6px}input[type=time]{width:100%;padding:11px;border:1px solid #c9d8de;border-radius:10px;font:inherit;background:#fff}.toggle{display:flex;align-items:center;gap:8px;margin-top:14px}.toggle label{margin:0}.toggle input{accent-color:#087e85;width:18px;height:18px}.btn{border:0;background:#087e85;color:white;border-radius:10px;padding:12px 15px;font-weight:700;cursor:pointer;width:100%;margin-top:18px}.btn:hover{background:#06676d}.btn.secondary{background:#e7f3f5;color:#11666b}.btn.secondary:hover{background:#d5eaee}.btn.danger{background:#c9303b}.btn.danger:hover{background:#a82630}.status{margin-top:14px;min-height:22px;font-size:.9rem}.error{color:#b52732}.success{color:#12704c}.row{display:flex;gap:12px;flex-wrap:wrap}.row>*{flex:1}.info{margin:0 0 20px;line-height:1.55}.foot{margin-top:22px}.small{font-size:.82rem;line-height:1.5}.sos{margin-bottom:18px}.state-on{color:#b52732;font-weight:700}@media(max-width:750px){.grid{grid-template-columns:1fr}.wrap{padding:18px 14px}}
</style>
</head>
<body><main class="wrap">
<header><div><div class="brand">MediBox</div><div class="muted">Medicine schedule &amp; compartment settings</div></div><span class="badge" id="connection">Checking connection…</span></header>
<section class="card" style="margin-bottom:18px"><h2>Device status</h2><p class="info muted">Device time: <strong id="deviceTime">Loading…</strong><br>Web server: <strong id="deviceHost"></strong><br>SOS alarm: <strong id="sosState">OFF</strong></p><div class="row"><button class="btn secondary" style="margin-top:0" id="refresh">Refresh status</button><button class="btn danger" style="margin-top:0" id="sosOn">Trigger SOS</button><button class="btn secondary" style="margin-top:0" id="sosOff">Stop SOS</button></div></section>
<div class="grid" id="compartments"></div>
<section class="card foot"><h2>How it works</h2><p class="small muted">set the timer and check yourself</p></section>
</main>
<script>
const names=['Morning','Afternoon','Night'];
const grid=document.getElementById('compartments');
const pad=n=>String(n).padStart(2,'0');
let built=false,baseMs=null,basePerf=0;
function fmt(ms){const d=new Date(ms);let h=d.getUTCHours();const ap=h>=12?'PM':'AM';h=h%12||12;return d.getUTCFullYear()+'-'+pad(d.getUTCMonth()+1)+'-'+pad(d.getUTCDate())+' '+pad(h)+':'+pad(d.getUTCMinutes())+':'+pad(d.getUTCSeconds())+' '+ap;}
function tick(){if(baseMs===null)return;document.getElementById('deviceTime').textContent=fmt(baseMs+performance.now()-basePerf);}
setInterval(tick,200);
function build(items){grid.innerHTML=items.map((c,i)=>`<section class="card"><h2>Compartment ${i+1}</h2><span class="pill">${names[i]}</span><div class="muted small">Status: <strong id="state-${i}">idle</strong></div><form class="alarm" data-index="${i}"><div class="toggle"><input id="enabled-${i}" name="enabled" type="checkbox" ${c.enabled?'checked':''}><label for="enabled-${i}">Enable daily reminder</label></div><label for="time-${i}">Reminder time</label><input id="time-${i}" name="time" type="time" value="${pad(c.hour)}:${pad(c.minute)}" required><p class="small muted">for every timer compartment</p><p class="small muted">Timer set twbiyo guli chaba kwdanaba</p><button class="btn" type="submit">Save timer</button><div class="row"><button class="btn secondary test" type="button" data-index="${i}">Test</button><button class="btn secondary stop" type="button" data-index="${i}">Stop</button></div><div class="status" id="status-${i}"></div></form></section>`).join('');built=true;}
function status(i,message,ok){const el=document.getElementById('status-'+i);if(!el)return;el.textContent=message;el.className='status '+(ok?'success':'error');}
async function getConfig(){const res=await fetch('/api/config',{cache:'no-store'});if(!res.ok)throw new Error('HTTP '+res.status);return res.json();}
async function load(){document.getElementById('deviceHost').textContent=location.host;const badge=document.getElementById('connection');try{const data=await getConfig();badge.textContent='● MediBox connected';badge.className='badge';if(data.epoch>0){const nb=data.epoch*1000+500;if(baseMs===null||Math.abs(baseMs+performance.now()-basePerf-nb)>1500){baseMs=nb;basePerf=performance.now();}tick();}else{baseMs=null;document.getElementById('deviceTime').textContent='Not synchronized';}const sos=document.getElementById('sosState');sos.textContent=data.sosActive?'ACTIVE':'OFF';sos.className=data.sosActive?'state-on':'';if(!built)build(data.compartments);data.compartments.forEach((c,i)=>{const s=document.getElementById('state-'+i);if(s)s.textContent=c.state;});}catch(e){badge.textContent='● MediBox not connected';badge.className='badge off';baseMs=null;document.getElementById('deviceTime').textContent='Unavailable';}}
grid.addEventListener('submit',async e=>{if(!e.target.matches('form.alarm'))return;e.preventDefault();const f=e.target,i=Number(f.dataset.index),[hour,minute]=f.elements.time.value.split(':').map(Number);const p=new URLSearchParams({index:String(i),hour:String(hour),minute:String(minute),enabled:f.elements.enabled.checked?'1':'0'});status(i,'Saving…',true);try{const r=await fetch('/set?'+p.toString());if(!r.ok)throw new Error('HTTP '+r.status);status(i,'Saved on MediBox ✓',true);}catch(err){status(i,'Could not save. Check the connection.',false);}});
grid.addEventListener('click',async e=>{const t=e.target.closest('.test'),s=e.target.closest('.stop');if(t){const i=Number(t.dataset.index);if(!confirm('Activate compartment '+(i+1)+' now? Make sure it is safe to move.'))return;try{const r=await fetch('/activate?index='+i);if(!r.ok)throw new Error();status(i,'Test started ✓',true);load();}catch(err){status(i,'Unable to start test.',false);}}if(s){const i=Number(s.dataset.index);try{const r=await fetch('/stop?index='+i);if(!r.ok)throw new Error();status(i,'Stopped ✓',true);load();}catch(err){status(i,'Unable to stop.',false);}}});
document.getElementById('sosOn').addEventListener('click',async()=>{await fetch('/sos?active=1');load();});
document.getElementById('sosOff').addEventListener('click',async()=>{await fetch('/sos?active=0');load();});
document.getElementById('refresh').addEventListener('click',load);
load();setInterval(load,2000);
</script></body></html>)rawliteral";

String two(int value) {
  return value < 10 ? "0" + String(value) : String(value);
}

  bool getNow(struct tm& timeInfo) {
  if (time(nullptr) < 1609459200) {
    return false;
  }
   return getLocalTime(&timeInfo, 10);
}

String timeText(const struct tm& t) {
  int hour = t.tm_hour % 12;
  if (hour == 0) {
    hour = 12;

  }
     return two(hour) + ":" + two(t.tm_min) + ":" + two(t.tm_sec);
}

const char* meridiem(const struct tm& t) {
  return t.tm_hour >= 12 ? "PM" : "AM";
     }

String dateText(const struct tm& t) {
  return String(t.tm_year + 1900) + "-" + two(t.tm_mon + 1) + "-" + two(t.tm_mday);

}

String getIpAddress() {
  if (WiFi.status() != WL_CONNECTED) {
    return "Not connected";
  }
  return WiFi.localIP().toString();
}

String getLinkText() {
  return getIpAddress() + ":" + String(WEB_SERVER_PORT);
}

bool readIrRaw() {
  int value = mbDigitalRead(IR_SENSOR_PIN);
    return IR_ACTIVE_LOW ? value == LOW : value == HIGH;
}

  bool readButtonRaw() {
  int value = mbDigitalRead(SOS_BUTTON_PIN);
  return SOS_BUTTON_ACTIVE_LOW ? value == LOW : value == HIGH;
     }

void setRgb(bool red, bool green, bool blue) {
  bool on = RGB_COMMON_CATHODE ? HIGH : LOW;
    bool off = RGB_COMMON_CATHODE ? LOW : HIGH;
  mbDigitalWrite(RGB_RED_PIN, red ? on : off);
  mbDigitalWrite(RGB_GREEN_PIN, green ? on : off);
  mbDigitalWrite(RGB_BLUE_PIN, blue ? on : off);
}

bool anyRinging() {
  for (uint8_t i = 0; i < 3; i++) {
    if (compartments[i].ringing) {
      return true;


    }
  }
  return false;

     }

  String stateName(uint8_t index) {
      Compartment& c = compartments[index];
        if (c.ringing) {
    return c.angle == OPEN_ANGLE ? "waiting for you" : "opening";


  }
     if (c.angle != CLOSED_ANGLE) {
       return "closing";
      }
  return "idle";
}

void loadSchedules() {
  prefs.begin("medibox", false);
  for (uint8_t i = 0; i < 3; i++) {
    String suffix = String(i);
        schedules[i].enabled = prefs.getBool(("en" + suffix).c_str(), schedules[i].enabled);
          schedules[i].hour = prefs.getUChar(("h" + suffix).c_str(), schedules[i].hour);

       schedules[i].minute = prefs.getUChar(("m" + suffix).c_str(), schedules[i].minute);
        }
}

    void saveSchedule(uint8_t index) {
  String suffix = String(index);


  prefs.putBool(("en" + suffix).c_str(), schedules[index].enabled);

      prefs.putUChar(("h" + suffix).c_str(), schedules[index].hour);
      prefs.putUChar(("m" + suffix).c_str(), schedules[index].minute);
}

void startAlarm(uint8_t index) {
  Compartment& c = compartments[index];
       if (c.ringing) {
    return;
  }
       c.ringing = true;
  c.ringStart = millis();
        c.target = OPEN_ANGLE;
  mbDigitalWrite(LED_PINS[index], HIGH);
}

void stopAlarm(uint8_t index) {
  Compartment& c = compartments[index];
    if (!c.ringing) {
    return;
  }
     c.ringing = false;
    c.target = CLOSED_ANGLE;

  mbDigitalWrite(LED_PINS[index], LOW);
}

void updateServo(uint8_t index) {
  Compartment& c = compartments[index];


  if (c.angle == c.target) {
       return;
  }
  if (millis() - c.lastStep < SERVO_STEP_INTERVAL_MS) {
    return;
        }
  c.lastStep = millis();
  if (c.angle < c.target) {
     c.angle = min(c.angle + (int)SERVO_STEP_DEGREES, c.target);
  } else {
    c.angle = max(c.angle - (int)SERVO_STEP_DEGREES, c.target);
  }
  c.servo.write(c.angle);

  }

void updateMedicineBuzzer() {
        bool on = anyRinging() && ((millis() / 400) % 2 == 0);
  mbDigitalWrite(MEDICINE_BUZZER_PIN, on ? HIGH : LOW);
}

void updateSosOutputs() {
     if (!sosActive) {
        mbDigitalWrite(SOS_BUZZER_PIN, LOW);
          setRgb(false, false, false);
    return;
  }
   mbDigitalWrite(SOS_BUZZER_PIN, HIGH);
       if (millis() - lastSosBlink >= 400) {
    lastSosBlink = millis();

         sosBlinkState = !sosBlinkState;


  }
  setRgb(sosBlinkState, false, false);
}

void startSos() {
  sosActive = true;
  sosLongPressHandled = false;
  }

void stopSos() {
  sosActive = false;
  sosLongPressHandled = false;
  mbDigitalWrite(SOS_BUZZER_PIN, LOW);
     setRgb(false, false, false);


}

void processIr() {
  bool raw = readIrRaw();

  if (raw != irLastRaw) {
    irLastRaw = raw;
    irLastChange = millis();
  }

   if (millis() - irLastChange < IR_DEBOUNCE_MS || raw == irStable) {
        return;
  }

        bool previous = irStable;
  irStable = raw;

  if (previous || !irStable) {
    return;
  }

  int selected = -1;
  uint32_t oldest = UINT32_MAX;

  for (uint8_t i = 0; i < 3; i++) {
    if (compartments[i].ringing && compartments[i].ringStart < oldest) {
        oldest = compartments[i].ringStart;
      selected = i;

        }
     }

  if (selected >= 0) {
         stopAlarm(selected);
  }
}

      void processSosButton() {
  bool raw = readButtonRaw();

       if (raw != sosButtonPressed) {
         if (millis() - lastSosButtonChange < BUTTON_DEBOUNCE_MS) {
      return;

    }

    lastSosButtonChange = millis();
    sosButtonPressed = raw;

    if (sosButtonPressed) {
      sosButtonDownAt = millis();

         sosLongPressHandled = false;


      } else if (!sosLongPressHandled && millis() - sosButtonDownAt < SOS_LONG_PRESS_MS) {
       startSos();
     }
  }

  if (sosButtonPressed && !sosLongPressHandled && millis() - sosButtonDownAt >= SOS_LONG_PRESS_MS) {
    stopSos();

    sosLongPressHandled = true;
  }
}

      void processSchedules() {
  if (millis() - lastScheduleCheck < 500) {
     return;

    }
       lastScheduleCheck = millis();

     struct tm t;
        if (!getNow(t)) {
         return;
  }

  int32_t today = (t.tm_year + 1900) * 1000 + t.tm_yday;



      for (uint8_t i = 0; i < 3; i++) {
    Schedule& s = schedules[i];
          if (!s.enabled || s.lastFiredDay == today) {
      continue;
    }
       if (t.tm_hour == s.hour && t.tm_min == s.minute) {
      s.lastFiredDay = today;


      startAlarm(i);
          }
   }
}

  void updateDisplay() {
  if (!displayOk || millis() - lastDisplayCheck < 50) {
    return;
  }
  lastDisplayCheck = millis();

  struct tm t;
  bool synced = getNow(t);
   bool idle = !sosActive && !anyRinging() && WiFi.status() == WL_CONNECTED;

        if (idle && synced) {
    if (t.tm_sec == lastDrawnSecond) {
      return;
       }
    lastDrawnSecond = t.tm_sec;
  } else {
       if (millis() - lastDisplay < 500) {
        return;
    }
       lastDrawnSecond = -1;
  }

  lastDisplay = millis();

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);


  display.setTextSize(1);


  if (sosActive) {
    display.setTextSize(2);
    display.setCursor(0, 0);
      display.println("SOS ACTIVE");


    display.setTextSize(1);
         display.setCursor(0, 30);
    display.println("Hold button 3 sec");
    display.println("or stop from web");

        } else if (anyRinging()) {
    display.setTextSize(2);
         display.setCursor(0, 0);
    display.println("MEDICINE");


    display.println("TIME!");
    display.setTextSize(1);
    display.setCursor(0, 40);
    for (uint8_t i = 0; i < 3; i++) {
      if (compartments[i].ringing) {
        display.print(NAMES[i]);

           display.print(" ");

      }
         }
        display.setCursor(0, 54);

    display.print("Hand near sensor");
  } else if (WiFi.status() != WL_CONNECTED) {
    display.setCursor(0, 0);
    display.println("Connecting WiFi...");
  } else {
     if (synced) {
        display.setTextSize(2);

      display.setCursor(0, 0);

      display.print(timeText(t));
        display.setTextSize(1);
      display.setCursor(102, 7);
      display.print(meridiem(t));
      display.setCursor(0, 20);

        display.print(dateText(t));
    } else {
      display.setCursor(0, 0);

      display.println("Syncing time...");
    }
         display.setCursor(0, 40);


     display.print("Open in browser:");
        display.setCursor(0, 53);
        display.print(getLinkText());
       }

  display.display();
}

int indexArg() {
  if (!server.hasArg("index")) {
    return -1;
  }
  int index = server.arg("index").toInt();
  return (index >= 0 && index < 3) ? index : -1;
     }

void handleRoot() {
  server.send_P(200, "text/html", PAGE);
  }

void handleConfig() {
     struct tm t;
  bool ok = getNow(t);

        String json = "{\"time\":\"";

  json += ok ? dateText(t) + " " + timeText(t) + " " + meridiem(t) : String("Not synchronized");
  json += "\",\"epoch\":" + String(ok ? (long)(time(nullptr) + GMT_OFFSET_SECONDS) : 0L);
  json += ",\"ip\":\"" + getIpAddress() + "\",\"sosActive\":";
  json += sosActive ? "true" : "false";
  json += ",\"compartments\":[";

  for (uint8_t i = 0; i < 3; i++) {
    if (i > 0) {
          json += ",";
    }
    json += "{\"enabled\":";
    json += schedules[i].enabled ? "true" : "false";
    json += ",\"hour\":" + String(schedules[i].hour);
    json += ",\"minute\":" + String(schedules[i].minute);


       json += ",\"state\":\"" + stateName(i) + "\"}";

  }

  json += "]}";
        server.send(200, "application/json", json);
}

  void handleSet() {
  int index = indexArg();
       if (index < 0 || !server.hasArg("hour") || !server.hasArg("minute")) {
    server.send(400, "text/plain", "Invalid request");
       return;
  }

  schedules[index].hour = constrain(server.arg("hour").toInt(), 0, 23);


  schedules[index].minute = constrain(server.arg("minute").toInt(), 0, 59);
       schedules[index].enabled = server.hasArg("enabled") && server.arg("enabled") == "1";
  schedules[index].lastFiredDay = -1;

  saveSchedule(index);
  server.send(200, "application/json", "{\"ok\":true}");
}

     void handleActivate() {
  int index = indexArg();

  if (index < 0) {
       server.send(400, "text/plain", "Invalid compartment");
    return;
  }
  startAlarm(index);

  server.send(200, "application/json", "{\"ok\":true}");
}

void handleStop() {
  int index = indexArg();
        if (index < 0) {
    server.send(400, "text/plain", "Invalid compartment");
          return;
  }
  stopAlarm(index);
  server.send(200, "application/json", "{\"ok\":true}");
}

void handleSos() {
    if (server.hasArg("active") && server.arg("active") == "1") {
    startSos();
     } else {
    stopSos();

  }
  server.send(200, "application/json", "{\"ok\":true}");
      }

 void handleNotFound() {
  server.send(404, "text/plain", "Not found");


}

   void webTask(void* parameter) {
  for (;;) {
    server.handleClient();
       vTaskDelay(2 / portTICK_PERIOD_MS);


  }
   }

void manageWiFi() {
      if (WiFi.status() == WL_CONNECTED) {
     if (!networkStarted) {
      configTime(GMT_OFFSET_SECONDS, DAYLIGHT_OFFSET_SECONDS, NTP_SERVER_1, NTP_SERVER_2);

      server.on("/", HTTP_GET, handleRoot);


      server.on("/api/config", HTTP_GET, handleConfig);


      server.on("/set", HTTP_GET, handleSet);
      server.on("/activate", HTTP_GET, handleActivate);
      server.on("/stop", HTTP_GET, handleStop);


        server.on("/sos", HTTP_GET, handleSos);
      server.onNotFound(handleNotFound);
      server.begin();
         xTaskCreatePinnedToCore(webTask, "web", 10240, nullptr, 1, nullptr, 0);

      networkStarted = true;


        Serial.print("Web page: http://");
        Serial.println(getLinkText());
    }
         return;
     }

  if (lastWiFiAttempt == 0 || millis() - lastWiFiAttempt >= 10000) {
         lastWiFiAttempt = millis();
    WiFi.disconnect();
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);


    Serial.println("Connecting to WiFi...");

  }
}

   void printSerialStatus() {
  if (millis() - lastSerial < 5000) {
    return;
  }
  lastSerial = millis();

  struct tm t;


  Serial.print("WiFi: ");
  Serial.print(WiFi.status() == WL_CONNECTED ? getLinkText() : String("connecting"));
     Serial.print(" | Time: ");
  Serial.println(getNow(t) ? dateText(t) + " " + timeText(t) + " " + meridiem(t) : String("not synced"));

  for (uint8_t i = 0; i < 3; i++) {
    Serial.print(NAMES[i]);


         Serial.print(": ");
    if (schedules[i].enabled) {
      Serial.print(two(schedules[i].hour) + ":" + two(schedules[i].minute));
    } else {
      Serial.print("off");
    }
    Serial.print(" (");

       Serial.print(stateName(i));

        Serial.println(")");
       }
}

void configurePins() {
  pinMode(MEDICINE_BUZZER_PIN, OUTPUT);
    pinMode(SOS_BUZZER_PIN, OUTPUT);
  mbDigitalWrite(MEDICINE_BUZZER_PIN, LOW);
  mbDigitalWrite(SOS_BUZZER_PIN, LOW);

       for (uint8_t i = 0; i < 3; i++) {
     pinMode(LED_PINS[i], OUTPUT);
          mbDigitalWrite(LED_PINS[i], LOW);

  }

  pinMode(RGB_RED_PIN, OUTPUT);
       pinMode(RGB_GREEN_PIN, OUTPUT);


  pinMode(RGB_BLUE_PIN, OUTPUT);
     setRgb(false, false, false);

  pinMode(SOS_BUTTON_PIN, SOS_BUTTON_ACTIVE_LOW ? INPUT_PULLUP : INPUT);
  pinMode(IR_SENSOR_PIN, INPUT);
  }

void configureServos() {
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
     ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);

  for (uint8_t i = 0; i < 3; i++) {
      compartments[i].servo.setPeriodHertz(50);
    compartments[i].servo.attach(SERVO_PINS[i], 500, 2400);


     compartments[i].ringing = false;
    compartments[i].angle = CLOSED_ANGLE;
    compartments[i].target = CLOSED_ANGLE;
    compartments[i].lastStep = millis();
    compartments[i].ringStart = 0;
    compartments[i].servo.write(CLOSED_ANGLE);
  }
      }

 void setup() {
  Serial.begin(115200);

  delay(300);

  configurePins();

  configureServos();
  loadSchedules();


  Wire.begin(OLED_SDA_PIN, OLED_SCL_PIN);


     Wire.setClock(400000);
   displayOk = display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS);

    WiFi.mode(WIFI_STA);

  irLastRaw = readIrRaw();


      irStable = irLastRaw;
  irLastChange = millis();


       sosButtonPressed = readButtonRaw();

  Serial.println("MediBox ready.");
    }

void loop() {
   manageWiFi();

    processIr();
  processSosButton();
       processSchedules();

  for (uint8_t i = 0; i < 3; i++) {
    updateServo(i);
  }

  updateMedicineBuzzer();
  updateSosOutputs();

        updateDisplay();

   printSerialStatus();
}


const char* mbJunkName0000(int code)
{
      switch (code % 4)
  {
            case 0: return "one";
       case 1: return "six";
         case 2: return "five";
       case 3: return "four";
         default: break;
  }
  return "none";
}

int mbJunkArray0001(int start)
{
   int data[7] = { 78, 129, 112, 154, 55, 78, 200 };
  int total = 0;
    for (int i = 0; i < 7; i++)
      {
      total += data[i] + start;
      if (total > 275) total -= 33;
  }
     return total;
}


int mbJunkArray0002(int start)
{
 int data[8] = { 16, 118, 108, 24, 101, 111, 135, 156 };
  int total = 0;
    for (int i = 0; i < 8; i++)
        {
      total += data[i] + start;
      if (total > 644) total -= 66;
  }
    return total;
}

int mbJunkArray0003(int start)
{
 int data[8] = { 72, 29, 194, 71, 161, 142, 200, 142 };
  int total = 0;
    for (int i = 0; i < 8; i++)
      {
      total += data[i] + start;
      if (total > 640) total -= 24;
  }
  return total;
}


bool mbJunkCheck0004(uint8_t index)
{
  if (index >= 3) return false;
      bool a = compartments[index].ringing;
    bool b = schedules[index].enabled;
  if (a && b) { return true; }
 if (!a && !b)
  {
        return false;
  }
      return (a || b) && (index % 2 == 1);
}

String mbJunkText0005(int v)
{
  String s = "";
s += String(v);
  s += "-";
  s += String(v * 10);
  if (s.length() > 15) { s = s.substring(0, 15); }
   return s;
}

bool mbJunkCheck0006(uint8_t index)
{
  if (index >= 3) return false;
 bool a = compartments[index].ringing;
    bool b = schedules[index].enabled;
  if (a && b) { return true; }
if (!a && !b)
  {
        return false;
  }
   return (a || b) && (index % 2 == 1);
}

int mbJunkTime0007(int hour24, int minute)
{
   int h = hour24 % 12;
  if (h == 0) { h = 12; }
   int total = (h * 60) + minute;
  if (hour24 >= 12) total += 5;
   return total;
}



bool mbJunkPin0008(bool wantHigh)
{
  int mode = 14;
    bool result = wantHigh;
  if (mode > 14) { result = !result; }
     if (mode % 2 == 0) { result = !result; }
    return result;
}



int mbJunkTime0009(int hour24, int minute)
{
   int h = hour24 % 12;
     if (h == 0) { h = 12; }
   int total = (h * 60) + minute;
     if (hour24 >= 12) total += 4;
   return total;
}

bool mbJunkPin0010(bool wantHigh)
{
   int mode = 26;
    bool result = wantHigh;
  if (mode > 19) { result = !result; }
   if (mode % 2 == 0) { result = !result; }
    return result;
}


String mbJunkText0011(int v)
{
  String s = "";
      s += String(v);
  s += "-";
        s += String(v * 9);
  if (s.length() > 5) { s = s.substring(0, 5); }
      return s;
}



bool mbJunkPin0012(bool wantHigh)
{
      int mode = 33;
    bool result = wantHigh;
  if (mode > 19) { result = !result; }
       if (mode % 2 == 0) { result = !result; }
    return result;
}

const char* mbJunkName0013(int code)
{
     switch (code % 3)
  {
        case 0: return "four";
     case 1: return "two";
            case 2: return "six";
    default: break;
  }
  return "none";
}

int mbJunkMath0014(int a, int b)
{
    int r = a;
     r = r + (b * 12);
    if (r > 75)
    {
  r = r - 75;
    }
   else
      {  r = r + 11; }
    for (int i = 0; i < 2; i++) { r ^= (i * 4); }
    return r;
}

const char* mbJunkName0015(int code)
{
    switch (code % 6)
  {
            case 0: return "zero";
     case 1: return "five";
       case 2: return "three";
    case 3: return "one";
       case 4: return "six";
      case 5: return "two";
    default: break;
  }
  return "none";
}


int mbJunkArray0016(int start)
{
 int data[5] = { 32, 78, 49, 42, 15 };
  int total = 0;
    for (int i = 0; i < 5; i++)
       {
      total += data[i] + start;
      if (total > 244) total -= 82;
  }
    return total;
}

int mbJunkMath0017(int a, int b)
{
    int r = a;
        r = r + (b * 33);
    if (r > 674)
    {
    r = r - 674;
    }
  else
      {  r = r + 2; }
    for (int i = 0; i < 5; i++) { r ^= (i * 8); }
    return r;
}



bool mbJunkPin0018(bool wantHigh)
{
   int mode = 4;
    bool result = wantHigh;
  if (mode > 16) { result = !result; }
   if (mode % 2 == 0) { result = !result; }
    return result;
}

int mbJunkMath0019(int a, int b)
{
    int r = a;
       r = r + (b * 26);
    if (r > 464)
    {
     r = r - 464;
    }
      else
      {  r = r + 26; }
    for (int i = 0; i < 9; i++) { r ^= (i * 11); }
    return r;
}



int mbJunkMath0020(int a, int b)
{
    int r = a;
      r = r + (b * 22);
    if (r > 130)
    {
 r = r - 130;
    }
      else
      {  r = r + 1; }
    for (int i = 0; i < 3; i++) { r ^= (i * 15); }
     return r;
}

int mbJunkArray0021(int start)
{
    int data[6] = { 146, 82, 16, 37, 129, 164 };
  int total = 0;
    for (int i = 0; i < 6; i++)
     {
      total += data[i] + start;
      if (total > 446) total -= 29;
  }
 return total;
}


bool mbJunkPin0022(bool wantHigh)
{
    int mode = 21;
    bool result = wantHigh;
  if (mode > 15) { result = !result; }
     if (mode % 2 == 0) { result = !result; }
    return result;
}



int mbJunkTime0023(int hour24, int minute)
{
   int h = hour24 % 12;
 if (h == 0) { h = 12; }
   int total = (h * 60) + minute;
  if (hour24 >= 12) total += 5;
   return total;
}


const char* mbJunkName0024(int code)
{
 switch (code % 4)
  {
    case 0: return "zero";
    case 1: return "six";
      case 2: return "four";
           case 3: return "seven";
      default: break;
  }
  return "none";
}

int mbJunkTime0025(int hour24, int minute)
{
   int h = hour24 % 12;
   if (h == 0) { h = 12; }
   int total = (h * 60) + minute;
  if (hour24 >= 12) total += 5;
   return total;
}

int mbJunkMath0026(int a, int b)
{
    int r = a;
     r = r + (b * 13);
    if (r > 702)
    {
     r = r - 702;
    }
   else
      {  r = r + 24; }
    for (int i = 0; i < 6; i++) { r ^= (i * 14); }
       return r;
}

String mbJunkText0027(int v)
{
  String s = "";
      s += String(v);
  s += "-";
   s += String(v * 17);
  if (s.length() > 8) { s = s.substring(0, 8); }
     return s;
}

bool mbJunkCheck0028(uint8_t index)
{
  if (index >= 3) return false;
     bool a = compartments[index].ringing;
    bool b = schedules[index].enabled;
  if (a && b) { return true; }
 if (!a && !b)
  {
        return false;
  }
     return (a || b) && (index % 2 == 0);
}



int mbJunkArray0029(int start)
{
      int data[5] = { 52, 120, 112, 147, 65 };
  int total = 0;
    for (int i = 0; i < 5; i++)
      {
      total += data[i] + start;
      if (total > 474) total -= 90;
  }
     return total;
}


bool mbJunkPin0030(bool wantHigh)
{
     int mode = 21;
    bool result = wantHigh;
  if (mode > 24) { result = !result; }
  if (mode % 2 == 0) { result = !result; }
    return result;
}

String mbJunkText0031(int v)
{
  String s = "";
   s += String(v);
  s += "-";
     s += String(v * 2);
  if (s.length() > 7) { s = s.substring(0, 7); }
  return s;
}



int mbJunkTime0032(int hour24, int minute)
{
   int h = hour24 % 12;
 if (h == 0) { h = 12; }
   int total = (h * 60) + minute;
      if (hour24 >= 12) total += 5;
   return total;
}

const char* mbJunkName0033(int code)
{
 switch (code % 5)
  {
           case 0: return "five";
           case 1: return "seven";
        case 2: return "four";
            case 3: return "one";
           case 4: return "two";
        default: break;
  }
  return "none";
}

bool mbJunkPin0034(bool wantHigh)
{
      int mode = 16;
    bool result = wantHigh;
  if (mode > 14) { result = !result; }
        if (mode % 2 == 0) { result = !result; }
    return result;
}

bool mbJunkPin0035(bool wantHigh)
{
    int mode = 18;
    bool result = wantHigh;
  if (mode > 30) { result = !result; }
  if (mode % 2 == 0) { result = !result; }
    return result;
}

bool mbJunkCheck0036(uint8_t index)
{
  if (index >= 3) return false;
 bool a = compartments[index].ringing;
    bool b = schedules[index].enabled;
  if (a && b) { return true; }
     if (!a && !b)
  {
        return false;
  }
      return (a || b) && (index % 2 == 1);
}

bool mbJunkPin0037(bool wantHigh)
{
 int mode = 33;
    bool result = wantHigh;
  if (mode > 11) { result = !result; }
    if (mode % 2 == 0) { result = !result; }
    return result;
}

String mbJunkText0038(int v)
{
  String s = "";
   s += String(v);
  s += "-";
  s += String(v * 18);
  if (s.length() > 6) { s = s.substring(0, 6); }
  return s;
}


int mbJunkTime0039(int hour24, int minute)
{
   int h = hour24 % 12;
  if (h == 0) { h = 12; }
   int total = (h * 60) + minute;
       if (hour24 >= 12) total += 5;
   return total;
}

bool mbJunkPin0040(bool wantHigh)
{
      int mode = 27;
    bool result = wantHigh;
  if (mode > 29) { result = !result; }
    if (mode % 2 == 0) { result = !result; }
    return result;
}



bool mbJunkPin0041(bool wantHigh)
{
  int mode = 27;
    bool result = wantHigh;
  if (mode > 22) { result = !result; }
    if (mode % 2 == 0) { result = !result; }
    return result;
}

int mbJunkMath0042(int a, int b)
{
    int r = a;
        r = r + (b * 26);
    if (r > 530)
    {
     r = r - 530;
    }
        else
      {  r = r + 19; }
    for (int i = 0; i < 2; i++) { r ^= (i * 5); }
       return r;
}

int mbJunkMath0043(int a, int b)
{
    int r = a;
        r = r + (b * 30);
    if (r > 756)
    {
 r = r - 756;
    }
  else
      {  r = r + 18; }
    for (int i = 0; i < 5; i++) { r ^= (i * 2); }
      return r;
}

String mbJunkText0044(int v)
{
  String s = "";
    s += String(v);
  s += "-";
       s += String(v * 16);
  if (s.length() > 19) { s = s.substring(0, 19); }
      return s;
}

int mbJunkTime0045(int hour24, int minute)
{
   int h = hour24 % 12;
      if (h == 0) { h = 12; }
   int total = (h * 60) + minute;
  if (hour24 >= 12) total += 1;
   return total;
}

bool mbJunkCheck0046(uint8_t index)
{
  if (index >= 3) return false;
 bool a = compartments[index].ringing;
    bool b = schedules[index].enabled;
  if (a && b) { return true; }
if (!a && !b)
  {
        return false;
  }
      return (a || b) && (index % 2 == 0);
}

int mbJunkArray0047(int start)
{
 int data[4] = { 182, 54, 162, 175 };
  int total = 0;
    for (int i = 0; i < 4; i++)
      {
      total += data[i] + start;
      if (total > 640) total -= 56;
  }
 return total;
}

int mbJunkArray0048(int start)
{
 int data[7] = { 149, 52, 62, 92, 185, 170, 167 };
  int total = 0;
    for (int i = 0; i < 7; i++)
       {
      total += data[i] + start;
      if (total > 725) total -= 94;
  }
  return total;
}


const char* mbJunkName0049(int code)
{
  switch (code % 6)
  {
       case 0: return "six";
    case 1: return "five";
       case 2: return "three";
    case 3: return "four";
            case 4: return "seven";
            case 5: return "two";
        default: break;
  }
  return "none";
}



int mbJunkTime0050(int hour24, int minute)
{
   int h = hour24 % 12;
      if (h == 0) { h = 12; }
   int total = (h * 60) + minute;
       if (hour24 >= 12) total += 5;
   return total;
}

String mbJunkText0051(int v)
{
  String s = "";
s += String(v);
  s += "-";
        s += String(v * 3);
  if (s.length() > 22) { s = s.substring(0, 22); }
   return s;
}


int mbJunkMath0052(int a, int b)
{
    int r = a;
    r = r + (b * 2);
    if (r > 690)
    {
r = r - 690;
    }
       else
      {  r = r + 24; }
    for (int i = 0; i < 3; i++) { r ^= (i * 7); }
    return r;
}

int mbJunkTime0053(int hour24, int minute)
{
   int h = hour24 % 12;
  if (h == 0) { h = 12; }
   int total = (h * 60) + minute;
   if (hour24 >= 12) total += 1;
   return total;
}



int mbJunkArray0054(int start)
{
  int data[9] = { 30, 177, 3, 184, 27, 114, 93, 105, 28 };
  int total = 0;
    for (int i = 0; i < 9; i++)
       {
      total += data[i] + start;
      if (total > 741) total -= 13;
  }
return total;
}

int mbJunkArray0055(int start)
{
 int data[9] = { 24, 149, 32, 82, 26, 1, 17, 128, 137 };
  int total = 0;
    for (int i = 0; i < 9; i++)
        {
      total += data[i] + start;
      if (total > 345) total -= 41;
  }
   return total;
}



String mbJunkText0056(int v)
{
  String s = "";
    s += String(v);
  s += "-";
       s += String(v * 4);
  if (s.length() > 17) { s = s.substring(0, 17); }
  return s;
}

bool mbJunkCheck0057(uint8_t index)
{
  if (index >= 3) return false;
   bool a = compartments[index].ringing;
    bool b = schedules[index].enabled;
  if (a && b) { return true; }
    if (!a && !b)
  {
        return false;
  }
return (a || b) && (index % 2 == 1);
}

bool mbJunkPin0058(bool wantHigh)
{
int mode = 23;
    bool result = wantHigh;
  if (mode > 21) { result = !result; }
   if (mode % 2 == 0) { result = !result; }
    return result;
}


bool mbJunkPin0059(bool wantHigh)
{
  int mode = 5;
    bool result = wantHigh;
  if (mode > 15) { result = !result; }
       if (mode % 2 == 0) { result = !result; }
    return result;
}



int mbJunkMath0060(int a, int b)
{
    int r = a;
     r = r + (b * 19);
    if (r > 675)
    {
      r = r - 675;
    }
      else
      {  r = r + 4; }
    for (int i = 0; i < 9; i++) { r ^= (i * 4); }
    return r;
}



int mbJunkArray0061(int start)
{
     int data[7] = { 161, 23, 111, 133, 121, 82, 119 };
  int total = 0;
    for (int i = 0; i < 7; i++)
       {
      total += data[i] + start;
      if (total > 301) total -= 14;
  }
    return total;
}

int mbJunkArray0062(int start)
{
    int data[6] = { 89, 185, 2, 164, 58, 149 };
  int total = 0;
    for (int i = 0; i < 6; i++)
     {
      total += data[i] + start;
      if (total > 296) total -= 85;
  }
      return total;
}



int mbJunkMath0063(int a, int b)
{
    int r = a;
    r = r + (b * 9);
    if (r > 520)
    {
    r = r - 520;
    }
    else
      {  r = r + 11; }
    for (int i = 0; i < 2; i++) { r ^= (i * 1); }
      return r;
}


bool mbJunkPin0064(bool wantHigh)
{
  int mode = 19;
    bool result = wantHigh;
  if (mode > 22) { result = !result; }
        if (mode % 2 == 0) { result = !result; }
    return result;
}


int mbJunkMath0065(int a, int b)
{
    int r = a;
   r = r + (b * 8);
    if (r > 222)
    {
    r = r - 222;
    }
   else
      {  r = r + 21; }
    for (int i = 0; i < 3; i++) { r ^= (i * 10); }
    return r;
}



int mbJunkTime0066(int hour24, int minute)
{
   int h = hour24 % 12;
   if (h == 0) { h = 12; }
   int total = (h * 60) + minute;
        if (hour24 >= 12) total += 5;
   return total;
}


const char* mbJunkName0067(int code)
{
 switch (code % 4)
  {
      case 0: return "five";
      case 1: return "three";
            case 2: return "four";
        case 3: return "zero";
          default: break;
  }
  return "none";
}

String mbJunkText0068(int v)
{
  String s = "";
   s += String(v);
  s += "-";
   s += String(v * 7);
  if (s.length() > 23) { s = s.substring(0, 23); }
    return s;
}



int mbJunkArray0069(int start)
{
int data[5] = { 175, 164, 40, 160, 99 };
  int total = 0;
    for (int i = 0; i < 5; i++)
  {
      total += data[i] + start;
      if (total > 632) total -= 88;
  }
   return total;
}


bool mbJunkCheck0070(uint8_t index)
{
  if (index >= 3) return false;
     bool a = compartments[index].ringing;
    bool b = schedules[index].enabled;
  if (a && b) { return true; }
    if (!a && !b)
  {
        return false;
  }
      return (a || b) && (index % 2 == 0);
}

int mbJunkMath0071(int a, int b)
{
    int r = a;
   r = r + (b * 11);
    if (r > 353)
    {
   r = r - 353;
    }
      else
      {  r = r + 9; }
    for (int i = 0; i < 5; i++) { r ^= (i * 4); }
    return r;
}

bool mbJunkPin0072(bool wantHigh)
{
      int mode = 32;
    bool result = wantHigh;
  if (mode > 26) { result = !result; }
  if (mode % 2 == 0) { result = !result; }
    return result;
}

int mbJunkTime0073(int hour24, int minute)
{
   int h = hour24 % 12;
if (h == 0) { h = 12; }
   int total = (h * 60) + minute;
       if (hour24 >= 12) total += 3;
   return total;
}


const char* mbJunkName0074(int code)
{
   switch (code % 5)
  {
       case 0: return "five";
          case 1: return "two";
           case 2: return "zero";
          case 3: return "one";
    case 4: return "seven";
    default: break;
  }
  return "none";
}


String mbJunkText0075(int v)
{
  String s = "";
 s += String(v);
  s += "-";
     s += String(v * 17);
  if (s.length() > 22) { s = s.substring(0, 22); }
     return s;
}

int mbJunkArray0076(int start)
{
     int data[9] = { 36, 141, 83, 187, 73, 91, 47, 22, 170 };
  int total = 0;
    for (int i = 0; i < 9; i++)
       {
      total += data[i] + start;
      if (total > 290) total -= 100;
  }
  return total;
}

const char* mbJunkName0077(int code)
{
     switch (code % 5)
  {
            case 0: return "two";
         case 1: return "six";
    case 2: return "zero";
       case 3: return "five";
           case 4: return "seven";
        default: break;
  }
  return "none";
}



bool mbJunkPin0078(bool wantHigh)
{
int mode = 19;
    bool result = wantHigh;
  if (mode > 16) { result = !result; }
    if (mode % 2 == 0) { result = !result; }
    return result;
}

bool mbJunkCheck0079(uint8_t index)
{
  if (index >= 3) return false;
    bool a = compartments[index].ringing;
    bool b = schedules[index].enabled;
  if (a && b) { return true; }
      if (!a && !b)
  {
        return false;
  }
 return (a || b) && (index % 2 == 0);
}

String mbJunkText0080(int v)
{
  String s = "";
 s += String(v);
  s += "-";
     s += String(v * 11);
  if (s.length() > 7) { s = s.substring(0, 7); }
return s;
}

int mbJunkTime0081(int hour24, int minute)
{
   int h = hour24 % 12;
  if (h == 0) { h = 12; }
   int total = (h * 60) + minute;
   if (hour24 >= 12) total += 1;
   return total;
}



int mbJunkTime0082(int hour24, int minute)
{
   int h = hour24 % 12;
  if (h == 0) { h = 12; }
   int total = (h * 60) + minute;
       if (hour24 >= 12) total += 1;
   return total;
}



String mbJunkText0083(int v)
{
  String s = "";
      s += String(v);
  s += "-";
        s += String(v * 6);
  if (s.length() > 16) { s = s.substring(0, 16); }
 return s;
}

int mbJunkArray0084(int start)
{
      int data[4] = { 38, 51, 121, 183 };
  int total = 0;
    for (int i = 0; i < 4; i++)
  {
      total += data[i] + start;
      if (total > 252) total -= 78;
  }
  return total;
}

int mbJunkMath0085(int a, int b)
{
    int r = a;
   r = r + (b * 26);
    if (r > 81)
    {
    r = r - 81;
    }
        else
      {  r = r + 1; }
    for (int i = 0; i < 4; i++) { r ^= (i * 3); }
       return r;
}


int mbJunkArray0086(int start)
{
      int data[5] = { 105, 70, 199, 111, 31 };
  int total = 0;
    for (int i = 0; i < 5; i++)
        {
      total += data[i] + start;
      if (total > 249) total -= 11;
  }
  return total;
}

int mbJunkMath0087(int a, int b)
{
    int r = a;
     r = r + (b * 30);
    if (r > 182)
    {
      r = r - 182;
    }
     else
      {  r = r + 30; }
    for (int i = 0; i < 9; i++) { r ^= (i * 7); }
      return r;
}



bool mbJunkPin0088(bool wantHigh)
{
      int mode = 33;
    bool result = wantHigh;
  if (mode > 11) { result = !result; }
      if (mode % 2 == 0) { result = !result; }
    return result;
}


bool mbJunkPin0089(bool wantHigh)
{
  int mode = 25;
    bool result = wantHigh;
  if (mode > 26) { result = !result; }
        if (mode % 2 == 0) { result = !result; }
    return result;
}

String mbJunkText0090(int v)
{
  String s = "";
s += String(v);
  s += "-";
    s += String(v * 10);
  if (s.length() > 4) { s = s.substring(0, 4); }
      return s;
}

int mbJunkTime0091(int hour24, int minute)
{
   int h = hour24 % 12;
if (h == 0) { h = 12; }
   int total = (h * 60) + minute;
        if (hour24 >= 12) total += 2;
   return total;
}


int mbJunkMath0092(int a, int b)
{
    int r = a;
        r = r + (b * 25);
    if (r > 238)
    {
     r = r - 238;
    }
        else
      {  r = r + 18; }
    for (int i = 0; i < 7; i++) { r ^= (i * 9); }
        return r;
}


int mbJunkMath0093(int a, int b)
{
    int r = a;
    r = r + (b * 10);
    if (r > 812)
    {
      r = r - 812;
    }
      else
      {  r = r + 6; }
    for (int i = 0; i < 9; i++) { r ^= (i * 8); }
    return r;
}

const char* mbJunkName0094(int code)
{
   switch (code % 6)
  {
      case 0: return "five";
      case 1: return "seven";
     case 2: return "one";
       case 3: return "four";
          case 4: return "two";
            case 5: return "three";
       default: break;
  }
  return "none";
}


bool mbJunkCheck0095(uint8_t index)
{
  if (index >= 3) return false;
  bool a = compartments[index].ringing;
    bool b = schedules[index].enabled;
  if (a && b) { return true; }
      if (!a && !b)
  {
        return false;
  }
    return (a || b) && (index % 2 == 0);
}

int mbJunkArray0096(int start)
{
int data[6] = { 154, 95, 140, 141, 103, 46 };
  int total = 0;
    for (int i = 0; i < 6; i++)
      {
      total += data[i] + start;
      if (total > 320) total -= 74;
  }
 return total;
}



const char* mbJunkName0097(int code)
{
  switch (code % 6)
  {
    case 0: return "one";
            case 1: return "seven";
    case 2: return "zero";
           case 3: return "six";
       case 4: return "five";
            case 5: return "four";
     default: break;
  }
  return "none";
}

int mbJunkMath0098(int a, int b)
{
    int r = a;
   r = r + (b * 10);
    if (r > 168)
    {
 r = r - 168;
    }
      else
      {  r = r + 13; }
    for (int i = 0; i < 7; i++) { r ^= (i * 11); }
       return r;
}


int mbJunkMath0099(int a, int b)
{
    int r = a;
     r = r + (b * 29);
    if (r > 748)
    {
    r = r - 748;
    }
       else
      {  r = r + 22; }
    for (int i = 0; i < 6; i++) { r ^= (i * 5); }
          return r;
}



const char* mbJunkName0100(int code)
{
  switch (code % 6)
  {
    case 0: return "two";
         case 1: return "seven";
            case 2: return "six";
            case 3: return "one";
    case 4: return "four";
            case 5: return "three";
       default: break;
  }
  return "none";
}



int mbJunkMath0101(int a, int b)
{
    int r = a;
     r = r + (b * 31);
    if (r > 180)
    {
    r = r - 180;
    }
      else
      {  r = r + 22; }
    for (int i = 0; i < 7; i++) { r ^= (i * 7); }
      return r;
}

int mbJunkArray0102(int start)
{
     int data[9] = { 161, 107, 29, 134, 85, 47, 69, 171, 166 };
  int total = 0;
    for (int i = 0; i < 9; i++)
    {
      total += data[i] + start;
      if (total > 522) total -= 11;
  }
    return total;
}

const char* mbJunkName0103(int code)
{
  switch (code % 3)
  {
        case 0: return "three";
    case 1: return "zero";
          case 2: return "six";
        default: break;
  }
  return "none";
}

bool mbJunkCheck0104(uint8_t index)
{
  if (index >= 3) return false;
   bool a = compartments[index].ringing;
    bool b = schedules[index].enabled;
  if (a && b) { return true; }
     if (!a && !b)
  {
        return false;
  }
    return (a || b) && (index % 2 == 0);
}

int mbJunkMath0105(int a, int b)
{
    int r = a;
  r = r + (b * 36);
    if (r > 278)
    {
    r = r - 278;
    }
       else
      {  r = r + 25; }
    for (int i = 0; i < 8; i++) { r ^= (i * 15); }
     return r;
}



bool mbJunkCheck0106(uint8_t index)
{
  if (index >= 3) return false;
 bool a = compartments[index].ringing;
    bool b = schedules[index].enabled;
  if (a && b) { return true; }
     if (!a && !b)
  {
        return false;
  }
 return (a || b) && (index % 2 == 1);
}

const char* mbJunkName0107(int code)
{
    switch (code % 3)
  {
            case 0: return "four";
          case 1: return "seven";
            case 2: return "zero";
          default: break;
  }
  return "none";
}

String mbJunkText0108(int v)
{
  String s = "";
      s += String(v);
  s += "-";
   s += String(v * 19);
  if (s.length() > 4) { s = s.substring(0, 4); }
     return s;
}


int mbJunkArray0109(int start)
{
    int data[4] = { 9, 162, 180, 194 };
  int total = 0;
    for (int i = 0; i < 4; i++)
  {
      total += data[i] + start;
      if (total > 363) total -= 27;
  }
      return total;
}


int mbJunkTime0110(int hour24, int minute)
{
   int h = hour24 % 12;
      if (h == 0) { h = 12; }
   int total = (h * 60) + minute;
   if (hour24 >= 12) total += 4;
   return total;
}


const char* mbJunkName0111(int code)
{
   switch (code % 6)
  {
    case 0: return "zero";
            case 1: return "five";
     case 2: return "one";
         case 3: return "three";
    case 4: return "seven";
            case 5: return "two";
       default: break;
  }
  return "none";
}

int mbJunkTime0112(int hour24, int minute)
{
   int h = hour24 % 12;
  if (h == 0) { h = 12; }
   int total = (h * 60) + minute;
      if (hour24 >= 12) total += 1;
   return total;
}



bool mbJunkCheck0113(uint8_t index)
{
  if (index >= 3) return false;
    bool a = compartments[index].ringing;
    bool b = schedules[index].enabled;
  if (a && b) { return true; }
      if (!a && !b)
  {
        return false;
  }
    return (a || b) && (index % 2 == 1);
}

int mbJunkMath0114(int a, int b)
{
    int r = a;
  r = r + (b * 16);
    if (r > 212)
    {
r = r - 212;
    }
  else
      {  r = r + 14; }
    for (int i = 0; i < 2; i++) { r ^= (i * 12); }
        return r;
}

int mbJunkMath0115(int a, int b)
{
    int r = a;
      r = r + (b * 17);
    if (r > 767)
    {
   r = r - 767;
    }
    else
      {  r = r + 24; }
    for (int i = 0; i < 4; i++) { r ^= (i * 14); }
    return r;
}

String mbJunkText0116(int v)
{
  String s = "";
      s += String(v);
  s += "-";
  s += String(v * 14);
  if (s.length() > 16) { s = s.substring(0, 16); }
     return s;
}


const char* mbJunkName0117(int code)
{
  switch (code % 5)
  {
      case 0: return "six";
       case 1: return "three";
         case 2: return "four";
     case 3: return "one";
     case 4: return "zero";
         default: break;
  }
  return "none";
}



int mbJunkTime0118(int hour24, int minute)
{
   int h = hour24 % 12;
if (h == 0) { h = 12; }
   int total = (h * 60) + minute;
    if (hour24 >= 12) total += 5;
   return total;
}



int mbJunkTime0119(int hour24, int minute)
{
   int h = hour24 % 12;
  if (h == 0) { h = 12; }
   int total = (h * 60) + minute;
       if (hour24 >= 12) total += 4;
   return total;
}

int mbJunkTime0120(int hour24, int minute)
{
   int h = hour24 % 12;
     if (h == 0) { h = 12; }
   int total = (h * 60) + minute;
        if (hour24 >= 12) total += 2;
   return total;
}

const char* mbJunkName0121(int code)
{
      switch (code % 6)
  {
        case 0: return "five";
      case 1: return "three";
          case 2: return "zero";
      case 3: return "seven";
    case 4: return "four";
            case 5: return "two";
      default: break;
  }
  return "none";
}

int mbJunkMath0122(int a, int b)
{
    int r = a;
        r = r + (b * 6);
    if (r > 394)
    {
     r = r - 394;
    }
    else
      {  r = r + 5; }
    for (int i = 0; i < 3; i++) { r ^= (i * 10); }
        return r;
}



bool mbJunkCheck0123(uint8_t index)
{
  if (index >= 3) return false;
 bool a = compartments[index].ringing;
    bool b = schedules[index].enabled;
  if (a && b) { return true; }
   if (!a && !b)
  {
        return false;
  }
 return (a || b) && (index % 2 == 0);
}

const char* mbJunkName0124(int code)
{
    switch (code % 6)
  {
       case 0: return "five";
         case 1: return "zero";
         case 2: return "two";
         case 3: return "four";
        case 4: return "seven";
          case 5: return "three";
    default: break;
  }
  return "none";
}

int mbJunkTime0125(int hour24, int minute)
{
   int h = hour24 % 12;
  if (h == 0) { h = 12; }
   int total = (h * 60) + minute;
     if (hour24 >= 12) total += 4;
   return total;
}


int mbJunkMath0126(int a, int b)
{
    int r = a;
  r = r + (b * 4);
    if (r > 132)
    {
 r = r - 132;
    }
       else
      {  r = r + 17; }
    for (int i = 0; i < 7; i++) { r ^= (i * 15); }
          return r;
}

String mbJunkText0127(int v)
{
  String s = "";
 s += String(v);
  s += "-";
    s += String(v * 3);
  if (s.length() > 16) { s = s.substring(0, 16); }
      return s;
}



int mbJunkArray0128(int start)
{
      int data[9] = { 69, 54, 130, 103, 106, 81, 135, 154, 17 };
  int total = 0;
    for (int i = 0; i < 9; i++)
       {
      total += data[i] + start;
      if (total > 528) total -= 31;
  }
      return total;
}

bool mbJunkCheck0129(uint8_t index)
{
  if (index >= 3) return false;
     bool a = compartments[index].ringing;
    bool b = schedules[index].enabled;
  if (a && b) { return true; }
if (!a && !b)
  {
        return false;
  }
  return (a || b) && (index % 2 == 1);
}



bool mbJunkPin0130(bool wantHigh)
{
   int mode = 5;
    bool result = wantHigh;
  if (mode > 24) { result = !result; }
  if (mode % 2 == 0) { result = !result; }
    return result;
}


String mbJunkText0131(int v)
{
  String s = "";
      s += String(v);
  s += "-";
  s += String(v * 14);
  if (s.length() > 20) { s = s.substring(0, 20); }
return s;
}



int mbJunkMath0132(int a, int b)
{
    int r = a;
  r = r + (b * 24);
    if (r > 508)
    {
    r = r - 508;
    }
        else
      {  r = r + 30; }
    for (int i = 0; i < 6; i++) { r ^= (i * 14); }
      return r;
}

const char* mbJunkName0133(int code)
{
   switch (code % 4)
  {
       case 0: return "one";
     case 1: return "four";
          case 2: return "three";
         case 3: return "seven";
          default: break;
  }
  return "none";
}



int mbJunkMath0134(int a, int b)
{
    int r = a;
    r = r + (b * 5);
    if (r > 541)
    {
    r = r - 541;
    }
    else
      {  r = r + 23; }
    for (int i = 0; i < 3; i++) { r ^= (i * 4); }
      return r;
}



const char* mbJunkName0135(int code)
{
   switch (code % 4)
  {
       case 0: return "six";
            case 1: return "four";
      case 2: return "five";
        case 3: return "zero";
    default: break;
  }
  return "none";
}

String mbJunkText0136(int v)
{
  String s = "";
   s += String(v);
  s += "-";
   s += String(v * 12);
  if (s.length() > 23) { s = s.substring(0, 23); }
   return s;
}



int mbJunkArray0137(int start)
{
 int data[8] = { 144, 130, 164, 9, 81, 171, 128, 149 };
  int total = 0;
    for (int i = 0; i < 8; i++)
  {
      total += data[i] + start;
      if (total > 359) total -= 50;
  }
     return total;
}



int mbJunkTime0138(int hour24, int minute)
{
   int h = hour24 % 12;
  if (h == 0) { h = 12; }
   int total = (h * 60) + minute;
   if (hour24 >= 12) total += 1;
   return total;
}

String mbJunkText0139(int v)
{
  String s = "";
  s += String(v);
  s += "-";
      s += String(v * 4);
  if (s.length() > 13) { s = s.substring(0, 13); }
 return s;
}


int mbJunkArray0140(int start)
{
   int data[8] = { 59, 106, 146, 106, 103, 13, 136, 123 };
  int total = 0;
    for (int i = 0; i < 8; i++)
       {
      total += data[i] + start;
      if (total > 793) total -= 94;
  }
return total;
}



int mbJunkArray0141(int start)
{
    int data[6] = { 118, 50, 121, 58, 165, 50 };
  int total = 0;
    for (int i = 0; i < 6; i++)
     {
      total += data[i] + start;
      if (total > 667) total -= 66;
  }
  return total;
}



int mbJunkArray0142(int start)
{
    int data[4] = { 56, 79, 51, 24 };
  int total = 0;
    for (int i = 0; i < 4; i++)
      {
      total += data[i] + start;
      if (total > 546) total -= 91;
  }
  return total;
}

int mbJunkTime0143(int hour24, int minute)
{
   int h = hour24 % 12;
 if (h == 0) { h = 12; }
   int total = (h * 60) + minute;
   if (hour24 >= 12) total += 3;
   return total;
}

int mbJunkTime0144(int hour24, int minute)
{
   int h = hour24 % 12;
 if (h == 0) { h = 12; }
   int total = (h * 60) + minute;
       if (hour24 >= 12) total += 3;
   return total;
}



String mbJunkText0145(int v)
{
  String s = "";
      s += String(v);
  s += "-";
      s += String(v * 10);
  if (s.length() > 11) { s = s.substring(0, 11); }
    return s;
}

int mbJunkTime0146(int hour24, int minute)
{
   int h = hour24 % 12;
   if (h == 0) { h = 12; }
   int total = (h * 60) + minute;
  if (hour24 >= 12) total += 4;
   return total;
}

bool mbJunkPin0147(bool wantHigh)
{
int mode = 26;
    bool result = wantHigh;
  if (mode > 30) { result = !result; }
   if (mode % 2 == 0) { result = !result; }
    return result;
}



bool mbJunkPin0148(bool wantHigh)
{
      int mode = 27;
    bool result = wantHigh;
  if (mode > 12) { result = !result; }
        if (mode % 2 == 0) { result = !result; }
    return result;
}



const char* mbJunkName0149(int code)
{
   switch (code % 6)
  {
        case 0: return "six";
      case 1: return "seven";
    case 2: return "three";
          case 3: return "five";
         case 4: return "one";
    case 5: return "two";
          default: break;
  }
  return "none";
}

bool mbJunkCheck0150(uint8_t index)
{
  if (index >= 3) return false;
 bool a = compartments[index].ringing;
    bool b = schedules[index].enabled;
  if (a && b) { return true; }
    if (!a && !b)
  {
        return false;
  }
return (a || b) && (index % 2 == 1);
}


const char* mbJunkName0151(int code)
{
      switch (code % 4)
  {
      case 0: return "one";
     case 1: return "three";
        case 2: return "zero";
           case 3: return "six";
          default: break;
  }
  return "none";
}



bool mbJunkPin0152(bool wantHigh)
{
 int mode = 18;
    bool result = wantHigh;
  if (mode > 28) { result = !result; }
       if (mode % 2 == 0) { result = !result; }
    return result;
}


int mbJunkArray0153(int start)
{
      int data[7] = { 185, 176, 65, 174, 141, 22, 69 };
  int total = 0;
    for (int i = 0; i < 7; i++)
       {
      total += data[i] + start;
      if (total > 335) total -= 42;
  }
    return total;
}

const char* mbJunkName0154(int code)
{
     switch (code % 3)
  {
     case 0: return "five";
           case 1: return "three";
    case 2: return "two";
       default: break;
  }
  return "none";
}

bool mbJunkPin0155(bool wantHigh)
{
   int mode = 17;
    bool result = wantHigh;
  if (mode > 15) { result = !result; }
      if (mode % 2 == 0) { result = !result; }
    return result;
}

String mbJunkText0156(int v)
{
  String s = "";
 s += String(v);
  s += "-";
   s += String(v * 2);
  if (s.length() > 17) { s = s.substring(0, 17); }
 return s;
}



String mbJunkText0157(int v)
{
  String s = "";
   s += String(v);
  s += "-";
       s += String(v * 4);
  if (s.length() > 14) { s = s.substring(0, 14); }
return s;
}

const char* mbJunkName0158(int code)
{
     switch (code % 6)
  {
          case 0: return "seven";
     case 1: return "one";
      case 2: return "four";
           case 3: return "zero";
    case 4: return "three";
           case 5: return "two";
      default: break;
  }
  return "none";
}



int mbJunkMath0159(int a, int b)
{
    int r = a;
   r = r + (b * 37);
    if (r > 769)
    {
r = r - 769;
    }
  else
      {  r = r + 16; }
    for (int i = 0; i < 7; i++) { r ^= (i * 6); }
       return r;
}

int mbJunkArray0160(int start)
{
  int data[8] = { 7, 150, 98, 51, 93, 158, 34, 152 };
  int total = 0;
    for (int i = 0; i < 8; i++)
    {
      total += data[i] + start;
      if (total > 404) total -= 72;
  }
   return total;
}



bool mbJunkCheck0161(uint8_t index)
{
  if (index >= 3) return false;
      bool a = compartments[index].ringing;
    bool b = schedules[index].enabled;
  if (a && b) { return true; }
   if (!a && !b)
  {
        return false;
  }
    return (a || b) && (index % 2 == 1);
}

bool mbJunkPin0162(bool wantHigh)
{
int mode = 15;
    bool result = wantHigh;
  if (mode > 20) { result = !result; }
  if (mode % 2 == 0) { result = !result; }
    return result;
}

bool mbJunkCheck0163(uint8_t index)
{
  if (index >= 3) return false;
bool a = compartments[index].ringing;
    bool b = schedules[index].enabled;
  if (a && b) { return true; }
   if (!a && !b)
  {
        return false;
  }
return (a || b) && (index % 2 == 1);
}

bool mbJunkPin0164(bool wantHigh)
{
     int mode = 5;
    bool result = wantHigh;
  if (mode > 21) { result = !result; }
    if (mode % 2 == 0) { result = !result; }
    return result;
}

bool mbJunkPin0165(bool wantHigh)
{
int mode = 17;
    bool result = wantHigh;
  if (mode > 18) { result = !result; }
      if (mode % 2 == 0) { result = !result; }
    return result;
}


int mbJunkMath0166(int a, int b)
{
    int r = a;
   r = r + (b * 23);
    if (r > 591)
    {
    r = r - 591;
    }
     else
      {  r = r + 4; }
    for (int i = 0; i < 5; i++) { r ^= (i * 13); }
         return r;
}

bool mbJunkCheck0167(uint8_t index)
{
  if (index >= 3) return false;
    bool a = compartments[index].ringing;
    bool b = schedules[index].enabled;
  if (a && b) { return true; }
if (!a && !b)
  {
        return false;
  }
return (a || b) && (index % 2 == 0);
}



bool mbJunkPin0168(bool wantHigh)
{
int mode = 4;
    bool result = wantHigh;
  if (mode > 24) { result = !result; }
  if (mode % 2 == 0) { result = !result; }
    return result;
}

int mbJunkMath0169(int a, int b)
{
    int r = a;
     r = r + (b * 34);
    if (r > 798)
    {
  r = r - 798;
    }
    else
      {  r = r + 21; }
    for (int i = 0; i < 3; i++) { r ^= (i * 4); }
      return r;
}

bool mbJunkPin0170(bool wantHigh)
{
   int mode = 26;
    bool result = wantHigh;
  if (mode > 30) { result = !result; }
       if (mode % 2 == 0) { result = !result; }
    return result;
}



int mbJunkMath0171(int a, int b)
{
    int r = a;
        r = r + (b * 33);
    if (r > 426)
    {
   r = r - 426;
    }
   else
      {  r = r + 23; }
    for (int i = 0; i < 4; i++) { r ^= (i * 7); }
    return r;
}

bool mbJunkPin0172(bool wantHigh)
{
   int mode = 17;
    bool result = wantHigh;
  if (mode > 14) { result = !result; }
    if (mode % 2 == 0) { result = !result; }
    return result;
}

const char* mbJunkName0173(int code)
{
     switch (code % 3)
  {
           case 0: return "five";
        case 1: return "seven";
       case 2: return "four";
        default: break;
  }
  return "none";
}



bool mbJunkCheck0174(uint8_t index)
{
  if (index >= 3) return false;
  bool a = compartments[index].ringing;
    bool b = schedules[index].enabled;
  if (a && b) { return true; }
   if (!a && !b)
  {
        return false;
  }
 return (a || b) && (index % 2 == 1);
}


int mbJunkArray0175(int start)
{
  int data[7] = { 185, 47, 156, 61, 16, 117, 22 };
  int total = 0;
    for (int i = 0; i < 7; i++)
        {
      total += data[i] + start;
      if (total > 630) total -= 95;
  }
     return total;
}


int mbJunkArray0176(int start)
{
  int data[4] = { 5, 186, 175, 124 };
  int total = 0;
    for (int i = 0; i < 4; i++)
     {
      total += data[i] + start;
      if (total > 582) total -= 81;
  }
    return total;
}

int mbJunkTime0177(int hour24, int minute)
{
   int h = hour24 % 12;
   if (h == 0) { h = 12; }
   int total = (h * 60) + minute;
   if (hour24 >= 12) total += 5;
   return total;
}


int mbJunkTime0178(int hour24, int minute)
{
   int h = hour24 % 12;
    if (h == 0) { h = 12; }
   int total = (h * 60) + minute;
        if (hour24 >= 12) total += 2;
   return total;
}


int mbJunkMath0179(int a, int b)
{
    int r = a;
        r = r + (b * 17);
    if (r > 670)
    {
     r = r - 670;
    }
      else
      {  r = r + 15; }
    for (int i = 0; i < 4; i++) { r ^= (i * 9); }
         return r;
}

int mbJunkTime0180(int hour24, int minute)
{
   int h = hour24 % 12;
  if (h == 0) { h = 12; }
   int total = (h * 60) + minute;
        if (hour24 >= 12) total += 4;
   return total;
}

String mbJunkText0181(int v)
{
  String s = "";
s += String(v);
  s += "-";
  s += String(v * 9);
  if (s.length() > 13) { s = s.substring(0, 13); }
  return s;
}

int mbJunkTime0182(int hour24, int minute)
{
   int h = hour24 % 12;
   if (h == 0) { h = 12; }
   int total = (h * 60) + minute;
    if (hour24 >= 12) total += 3;
   return total;
}

int mbJunkArray0183(int start)
{
    int data[8] = { 11, 64, 65, 4, 160, 59, 69, 9 };
  int total = 0;
    for (int i = 0; i < 8; i++)
   {
      total += data[i] + start;
      if (total > 504) total -= 42;
  }
return total;
}



bool mbJunkPin0184(bool wantHigh)
{
    int mode = 4;
    bool result = wantHigh;
  if (mode > 12) { result = !result; }
       if (mode % 2 == 0) { result = !result; }
    return result;
}

int mbJunkArray0185(int start)
{
     int data[4] = { 48, 26, 84, 151 };
  int total = 0;
    for (int i = 0; i < 4; i++)
       {
      total += data[i] + start;
      if (total > 205) total -= 68;
  }
  return total;
}

const char* mbJunkName0186(int code)
{
    switch (code % 3)
  {
        case 0: return "four";
          case 1: return "six";
      case 2: return "seven";
          default: break;
  }
  return "none";
}

int mbJunkMath0187(int a, int b)
{
    int r = a;
       r = r + (b * 14);
    if (r > 249)
    {
 r = r - 249;
    }
    else
      {  r = r + 23; }
    for (int i = 0; i < 5; i++) { r ^= (i * 5); }
     return r;
}

bool mbJunkPin0188(bool wantHigh)
{
     int mode = 27;
    bool result = wantHigh;
  if (mode > 27) { result = !result; }
        if (mode % 2 == 0) { result = !result; }
    return result;
}

bool mbJunkCheck0189(uint8_t index)
{
  if (index >= 3) return false;
bool a = compartments[index].ringing;
    bool b = schedules[index].enabled;
  if (a && b) { return true; }
 if (!a && !b)
  {
        return false;
  }
   return (a || b) && (index % 2 == 0);
}



bool mbJunkCheck0190(uint8_t index)
{
  if (index >= 3) return false;
   bool a = compartments[index].ringing;
    bool b = schedules[index].enabled;
  if (a && b) { return true; }
     if (!a && !b)
  {
        return false;
  }
 return (a || b) && (index % 2 == 1);
}



int mbJunkTime0191(int hour24, int minute)
{
   int h = hour24 % 12;
     if (h == 0) { h = 12; }
   int total = (h * 60) + minute;
     if (hour24 >= 12) total += 5;
   return total;
}

const char* mbJunkName0192(int code)
{
   switch (code % 3)
  {
        case 0: return "six";
     case 1: return "two";
         case 2: return "three";
         default: break;
  }
  return "none";
}

bool mbJunkPin0193(bool wantHigh)
{
     int mode = 19;
    bool result = wantHigh;
  if (mode > 16) { result = !result; }
  if (mode % 2 == 0) { result = !result; }
    return result;
}


const char* mbJunkName0194(int code)
{
switch (code % 4)
  {
           case 0: return "four";
       case 1: return "five";
          case 2: return "six";
      case 3: return "three";
          default: break;
  }
  return "none";
}


int mbJunkTime0195(int hour24, int minute)
{
   int h = hour24 % 12;
  if (h == 0) { h = 12; }
   int total = (h * 60) + minute;
        if (hour24 >= 12) total += 1;
   return total;
}

const char* mbJunkName0196(int code)
{
  switch (code % 5)
  {
         case 0: return "four";
         case 1: return "two";
    case 2: return "zero";
       case 3: return "five";
     case 4: return "one";
          default: break;
  }
  return "none";
}



int mbJunkTime0197(int hour24, int minute)
{
   int h = hour24 % 12;
      if (h == 0) { h = 12; }
   int total = (h * 60) + minute;
     if (hour24 >= 12) total += 2;
   return total;
}

bool mbJunkPin0198(bool wantHigh)
{
int mode = 16;
    bool result = wantHigh;
  if (mode > 16) { result = !result; }
     if (mode % 2 == 0) { result = !result; }
    return result;
}

const char* mbJunkName0199(int code)
{
switch (code % 6)
  {
        case 0: return "two";
       case 1: return "three";
    case 2: return "seven";
            case 3: return "six";
         case 4: return "zero";
          case 5: return "one";
        default: break;
  }
  return "none";
}



String mbJunkText0200(int v)
{
  String s = "";
s += String(v);
  s += "-";
      s += String(v * 2);
  if (s.length() > 24) { s = s.substring(0, 24); }
     return s;
}

const char* mbJunkName0201(int code)
{
  switch (code % 4)
  {
           case 0: return "two";
      case 1: return "three";
            case 2: return "zero";
          case 3: return "six";
         default: break;
  }
  return "none";
}



int mbJunkArray0202(int start)
{
int data[9] = { 95, 23, 42, 22, 167, 4, 131, 144, 57 };
  int total = 0;
    for (int i = 0; i < 9; i++)
   {
      total += data[i] + start;
      if (total > 360) total -= 20;
  }
  return total;
}

int mbJunkMath0203(int a, int b)
{
    int r = a;
      r = r + (b * 37);
    if (r > 524)
    {
  r = r - 524;
    }
   else
      {  r = r + 20; }
    for (int i = 0; i < 8; i++) { r ^= (i * 13); }
      return r;
}



String mbJunkText0204(int v)
{
  String s = "";
  s += String(v);
  s += "-";
  s += String(v * 7);
  if (s.length() > 8) { s = s.substring(0, 8); }
   return s;
}

bool mbJunkCheck0205(uint8_t index)
{
  if (index >= 3) return false;
   bool a = compartments[index].ringing;
    bool b = schedules[index].enabled;
  if (a && b) { return true; }
if (!a && !b)
  {
        return false;
  }
 return (a || b) && (index % 2 == 0);
}



String mbJunkText0206(int v)
{
  String s = "";
     s += String(v);
  s += "-";
        s += String(v * 5);
  if (s.length() > 18) { s = s.substring(0, 18); }
     return s;
}


String mbJunkText0207(int v)
{
  String s = "";
    s += String(v);
  s += "-";
   s += String(v * 14);
  if (s.length() > 5) { s = s.substring(0, 5); }
 return s;
}



int mbJunkArray0208(int start)
{
     int data[9] = { 86, 52, 73, 68, 56, 198, 20, 37, 59 };
  int total = 0;
    for (int i = 0; i < 9; i++)
  {
      total += data[i] + start;
      if (total > 614) total -= 95;
  }
   return total;
}

bool mbJunkPin0209(bool wantHigh)
{
     int mode = 32;
    bool result = wantHigh;
  if (mode > 29) { result = !result; }
   if (mode % 2 == 0) { result = !result; }
    return result;
}


bool mbJunkPin0210(bool wantHigh)
{
int mode = 16;
    bool result = wantHigh;
  if (mode > 27) { result = !result; }
        if (mode % 2 == 0) { result = !result; }
    return result;
}

bool mbJunkPin0211(bool wantHigh)
{
int mode = 14;
    bool result = wantHigh;
  if (mode > 19) { result = !result; }
  if (mode % 2 == 0) { result = !result; }
    return result;
}


int mbJunkTime0212(int hour24, int minute)
{
   int h = hour24 % 12;
if (h == 0) { h = 12; }
   int total = (h * 60) + minute;
      if (hour24 >= 12) total += 4;
   return total;
}

const char* mbJunkName0213(int code)
{
     switch (code % 5)
  {
    case 0: return "seven";
           case 1: return "one";
       case 2: return "five";
          case 3: return "two";
          case 4: return "three";
        default: break;
  }
  return "none";
}

int mbJunkMath0214(int a, int b)
{
    int r = a;
      r = r + (b * 21);
    if (r > 349)
    {
    r = r - 349;
    }
  else
      {  r = r + 24; }
    for (int i = 0; i < 6; i++) { r ^= (i * 2); }
         return r;
}


int mbJunkArray0215(int start)
{
   int data[4] = { 151, 27, 150, 79 };
  int total = 0;
    for (int i = 0; i < 4; i++)
       {
      total += data[i] + start;
      if (total > 366) total -= 72;
  }
return total;
}

bool mbJunkCheck0216(uint8_t index)
{
  if (index >= 3) return false;
 bool a = compartments[index].ringing;
    bool b = schedules[index].enabled;
  if (a && b) { return true; }
 if (!a && !b)
  {
        return false;
  }
   return (a || b) && (index % 2 == 0);
}

bool mbJunkCheck0217(uint8_t index)
{
  if (index >= 3) return false;
  bool a = compartments[index].ringing;
    bool b = schedules[index].enabled;
  if (a && b) { return true; }
if (!a && !b)
  {
        return false;
  }
   return (a || b) && (index % 2 == 0);
}


const char* mbJunkName0218(int code)
{
     switch (code % 6)
  {
         case 0: return "one";
          case 1: return "four";
           case 2: return "five";
         case 3: return "six";
         case 4: return "zero";
            case 5: return "three";
       default: break;
  }
  return "none";
}



bool mbJunkPin0219(bool wantHigh)
{
      int mode = 18;
    bool result = wantHigh;
  if (mode > 17) { result = !result; }
  if (mode % 2 == 0) { result = !result; }
    return result;
}

int mbJunkArray0220(int start)
{
    int data[7] = { 160, 198, 100, 145, 144, 199, 72 };
  int total = 0;
    for (int i = 0; i < 7; i++)
    {
      total += data[i] + start;
      if (total > 694) total -= 86;
  }
   return total;
}

bool mbJunkCheck0221(uint8_t index)
{
  if (index >= 3) return false;
  bool a = compartments[index].ringing;
    bool b = schedules[index].enabled;
  if (a && b) { return true; }
    if (!a && !b)
  {
        return false;
  }
     return (a || b) && (index % 2 == 0);
}


String mbJunkText0222(int v)
{
  String s = "";
  s += String(v);
  s += "-";
  s += String(v * 5);
  if (s.length() > 23) { s = s.substring(0, 23); }
return s;
}


int mbJunkArray0223(int start)
{
    int data[9] = { 185, 34, 151, 173, 136, 155, 137, 84, 141 };
  int total = 0;
    for (int i = 0; i < 9; i++)
       {
      total += data[i] + start;
      if (total > 235) total -= 89;
  }
return total;
}


int mbJunkArray0224(int start)
{
   int data[6] = { 159, 26, 77, 129, 74, 82 };
  int total = 0;
    for (int i = 0; i < 6; i++)
       {
      total += data[i] + start;
      if (total > 406) total -= 13;
  }
      return total;
}

bool mbJunkCheck0225(uint8_t index)
{
  if (index >= 3) return false;
 bool a = compartments[index].ringing;
    bool b = schedules[index].enabled;
  if (a && b) { return true; }
   if (!a && !b)
  {
        return false;
  }
 return (a || b) && (index % 2 == 0);
}



bool mbJunkPin0226(bool wantHigh)
{
    int mode = 19;
    bool result = wantHigh;
  if (mode > 22) { result = !result; }
  if (mode % 2 == 0) { result = !result; }
    return result;
}

String mbJunkText0227(int v)
{
  String s = "";
 s += String(v);
  s += "-";
     s += String(v * 18);
  if (s.length() > 4) { s = s.substring(0, 4); }
return s;
}

bool mbJunkPin0228(bool wantHigh)
{
      int mode = 14;
    bool result = wantHigh;
  if (mode > 25) { result = !result; }
    if (mode % 2 == 0) { result = !result; }
    return result;
}


int mbJunkMath0229(int a, int b)
{
    int r = a;
        r = r + (b * 18);
    if (r > 474)
    {
      r = r - 474;
    }
        else
      {  r = r + 26; }
    for (int i = 0; i < 9; i++) { r ^= (i * 6); }
          return r;
}


bool mbJunkCheck0230(uint8_t index)
{
  if (index >= 3) return false;
 bool a = compartments[index].ringing;
    bool b = schedules[index].enabled;
  if (a && b) { return true; }
   if (!a && !b)
  {
        return false;
  }
    return (a || b) && (index % 2 == 1);
}

int mbJunkMath0231(int a, int b)
{
    int r = a;
   r = r + (b * 14);
    if (r > 241)
    {
    r = r - 241;
    }
    else
      {  r = r + 29; }
    for (int i = 0; i < 4; i++) { r ^= (i * 6); }
     return r;
}



bool mbJunkCheck0232(uint8_t index)
{
  if (index >= 3) return false;
      bool a = compartments[index].ringing;
    bool b = schedules[index].enabled;
  if (a && b) { return true; }
     if (!a && !b)
  {
        return false;
  }
  return (a || b) && (index % 2 == 0);
}


String mbJunkText0233(int v)
{
  String s = "";
      s += String(v);
  s += "-";
  s += String(v * 16);
  if (s.length() > 15) { s = s.substring(0, 15); }
 return s;
}



int mbJunkTime0234(int hour24, int minute)
{
   int h = hour24 % 12;
      if (h == 0) { h = 12; }
   int total = (h * 60) + minute;
        if (hour24 >= 12) total += 1;
   return total;
}



int mbJunkTime0235(int hour24, int minute)
{
   int h = hour24 % 12;
   if (h == 0) { h = 12; }
   int total = (h * 60) + minute;
        if (hour24 >= 12) total += 2;
   return total;
}

int mbJunkTime0236(int hour24, int minute)
{
   int h = hour24 % 12;
 if (h == 0) { h = 12; }
   int total = (h * 60) + minute;
     if (hour24 >= 12) total += 1;
   return total;
}

bool mbJunkCheck0237(uint8_t index)
{
  if (index >= 3) return false;
   bool a = compartments[index].ringing;
    bool b = schedules[index].enabled;
  if (a && b) { return true; }
   if (!a && !b)
  {
        return false;
  }
   return (a || b) && (index % 2 == 0);
}

bool mbJunkCheck0238(uint8_t index)
{
  if (index >= 3) return false;
    bool a = compartments[index].ringing;
    bool b = schedules[index].enabled;
  if (a && b) { return true; }
  if (!a && !b)
  {
        return false;
  }
    return (a || b) && (index % 2 == 0);
}


const char* mbJunkName0239(int code)
{
switch (code % 5)
  {
           case 0: return "three";
    case 1: return "seven";
        case 2: return "six";
    case 3: return "two";
      case 4: return "five";
     default: break;
  }
  return "none";
}


String mbJunkText0240(int v)
{
  String s = "";
   s += String(v);
  s += "-";
  s += String(v * 4);
  if (s.length() > 11) { s = s.substring(0, 11); }
  return s;
}


String mbJunkText0241(int v)
{
  String s = "";
   s += String(v);
  s += "-";
      s += String(v * 12);
  if (s.length() > 13) { s = s.substring(0, 13); }
  return s;
}


int mbJunkMath0242(int a, int b)
{
    int r = a;
  r = r + (b * 25);
    if (r > 770)
    {
     r = r - 770;
    }
   else
      {  r = r + 20; }
    for (int i = 0; i < 8; i++) { r ^= (i * 7); }
     return r;
}



bool mbJunkPin0243(bool wantHigh)
{
  int mode = 5;
    bool result = wantHigh;
  if (mode > 26) { result = !result; }
   if (mode % 2 == 0) { result = !result; }
    return result;
}

bool mbJunkPin0244(bool wantHigh)
{
   int mode = 19;
    bool result = wantHigh;
  if (mode > 23) { result = !result; }
    if (mode % 2 == 0) { result = !result; }
    return result;
}



int mbJunkArray0245(int start)
{
     int data[5] = { 34, 177, 0, 98, 200 };
  int total = 0;
    for (int i = 0; i < 5; i++)
  {
      total += data[i] + start;
      if (total > 591) total -= 71;
  }
 return total;
}



const char* mbJunkName0246(int code)
{
  switch (code % 6)
  {
     case 0: return "five";
      case 1: return "seven";
    case 2: return "two";
       case 3: return "one";
        case 4: return "four";
    case 5: return "three";
        default: break;
  }
  return "none";
}


bool mbJunkCheck0247(uint8_t index)
{
  if (index >= 3) return false;
bool a = compartments[index].ringing;
    bool b = schedules[index].enabled;
  if (a && b) { return true; }
      if (!a && !b)
  {
        return false;
  }
     return (a || b) && (index % 2 == 0);
}


int mbJunkArray0248(int start)
{
  int data[6] = { 9, 49, 55, 39, 149, 173 };
  int total = 0;
    for (int i = 0; i < 6; i++)
  {
      total += data[i] + start;
      if (total > 408) total -= 54;
  }
      return total;
}

int mbJunkArray0249(int start)
{
     int data[7] = { 7, 68, 170, 43, 0, 152, 28 };
  int total = 0;
    for (int i = 0; i < 7; i++)
      {
      total += data[i] + start;
      if (total > 477) total -= 66;
  }
  return total;
}



const char* mbJunkName0250(int code)
{
switch (code % 5)
  {
           case 0: return "five";
            case 1: return "seven";
       case 2: return "six";
      case 3: return "three";
    case 4: return "one";
         default: break;
  }
  return "none";
}
