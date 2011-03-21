void abrt() {
 *(int*)(0) = 1; 
}
void test_i(int i0) { 
	if (i0 != 1550815723) { printf("test_i failed\n"); abrt(); }
	
} 
void test_f(float f0) { 
	if (f0 != 4058403.25492562f) { printf("test_f failed\n"); abrt(); }
	
} 
void test_d(double d0) { 
	if (d0 != 9389619.494705920) { printf("test_d failed\n"); abrt(); }
	
} 
void test_i_i(int i0, int i1) { 
	if (i0 != 1331402918) { printf("test_i_i failed\n"); abrt(); }
	if (i1 != 1133231918) { printf("test_i_i failed\n"); abrt(); }
	
} 
void test_f_i(float f0, int i1) { 
	if (f0 != 20770.9938693768f) { printf("test_f_i failed\n"); abrt(); }
	if (i1 != 1004363255) { printf("test_f_i failed\n"); abrt(); }
	
} 
void test_d_i(double d0, int i1) { 
	if (d0 != 7042894.533779740) { printf("test_d_i failed\n"); abrt(); }
	if (i1 != 1464748280) { printf("test_d_i failed\n"); abrt(); }
	
} 
void test_i_f(int i0, float f1) { 
	if (i0 != 424304409) { printf("test_i_f failed\n"); abrt(); }
	if (f1 != 948810.232965052f) { printf("test_i_f failed\n"); abrt(); }
	
} 
void test_f_f(float f0, float f1) { 
	if (f0 != 9680162.75195147f) { printf("test_f_f failed\n"); abrt(); }
	if (f1 != 1378646.09046108f) { printf("test_f_f failed\n"); abrt(); }
	
} 
void test_d_f(double d0, float f1) { 
	if (d0 != 6523872.773048110) { printf("test_d_f failed\n"); abrt(); }
	if (f1 != 9140482.21035497f) { printf("test_d_f failed\n"); abrt(); }
	
} 
void test_i_d(int i0, double d1) { 
	if (i0 != 1964580763) { printf("test_i_d failed\n"); abrt(); }
	if (d1 != 9066496.50046180) { printf("test_i_d failed\n"); abrt(); }
	
} 
void test_f_d(float f0, double d1) { 
	if (f0 != 2961097.54242053f) { printf("test_f_d failed\n"); abrt(); }
	if (d1 != 998549.4177676560) { printf("test_f_d failed\n"); abrt(); }
	
} 
void test_d_d(double d0, double d1) { 
	if (d0 != 5387731.395467270) { printf("test_d_d failed\n"); abrt(); }
	if (d1 != 7311544.642524450) { printf("test_d_d failed\n"); abrt(); }
	
} 
void test_i_i_i(int i0, int i1, int i2) { 
	if (i0 != 1312114750) { printf("test_i_i_i failed\n"); abrt(); }
	if (i1 != 1902236726) { printf("test_i_i_i failed\n"); abrt(); }
	if (i2 != 1675655795) { printf("test_i_i_i failed\n"); abrt(); }
	
} 
void test_f_i_i(float f0, int i1, int i2) { 
	if (f0 != 9160964.45566129f) { printf("test_f_i_i failed\n"); abrt(); }
	if (i1 != 1406971490) { printf("test_f_i_i failed\n"); abrt(); }
	if (i2 != 1028074056) { printf("test_f_i_i failed\n"); abrt(); }
	
} 
void test_d_i_i(double d0, int i1, int i2) { 
	if (d0 != 1462254.723497050) { printf("test_d_i_i failed\n"); abrt(); }
	if (i1 != 1107590144) { printf("test_d_i_i failed\n"); abrt(); }
	if (i2 != 1053669743) { printf("test_d_i_i failed\n"); abrt(); }
	
} 
void test_i_f_i(int i0, float f1, int i2) { 
	if (i0 != 211598425) { printf("test_i_f_i failed\n"); abrt(); }
	if (f1 != 3069857.15856335f) { printf("test_i_f_i failed\n"); abrt(); }
	if (i2 != 448726329) { printf("test_i_f_i failed\n"); abrt(); }
	
} 
void test_f_f_i(float f0, float f1, int i2) { 
	if (f0 != 4814250.20289493f) { printf("test_f_f_i failed\n"); abrt(); }
	if (f1 != 8393294.75790475f) { printf("test_f_f_i failed\n"); abrt(); }
	if (i2 != 1638099258) { printf("test_f_f_i failed\n"); abrt(); }
	
} 
void test_d_f_i(double d0, float f1, int i2) { 
	if (d0 != 4577402.351084920) { printf("test_d_f_i failed\n"); abrt(); }
	if (f1 != 2056169.60008328f) { printf("test_d_f_i failed\n"); abrt(); }
	if (i2 != 677791258) { printf("test_d_f_i failed\n"); abrt(); }
	
} 
void test_i_d_i(int i0, double d1, int i2) { 
	if (i0 != 766396665) { printf("test_i_d_i failed\n"); abrt(); }
	if (d1 != 4970507.369126020) { printf("test_i_d_i failed\n"); abrt(); }
	if (i2 != 269079978) { printf("test_i_d_i failed\n"); abrt(); }
	
} 
void test_f_d_i(float f0, double d1, int i2) { 
	if (f0 != 5164066.53669417f) { printf("test_f_d_i failed\n"); abrt(); }
	if (d1 != 3738497.158861730) { printf("test_f_d_i failed\n"); abrt(); }
	if (i2 != 1004182640) { printf("test_f_d_i failed\n"); abrt(); }
	
} 
void test_d_d_i(double d0, double d1, int i2) { 
	if (d0 != 3339444.458641910) { printf("test_d_d_i failed\n"); abrt(); }
	if (d1 != 813764.7216346620) { printf("test_d_d_i failed\n"); abrt(); }
	if (i2 != 1516608368) { printf("test_d_d_i failed\n"); abrt(); }
	
} 
void test_i_i_f(int i0, int i1, float f2) { 
	if (i0 != 1165667352) { printf("test_i_i_f failed\n"); abrt(); }
	if (i1 != 1242328201) { printf("test_i_i_f failed\n"); abrt(); }
	if (f2 != 4256874.75503832f) { printf("test_i_i_f failed\n"); abrt(); }
	
} 
void test_f_i_f(float f0, int i1, float f2) { 
	if (f0 != 4994097.8691405f) { printf("test_f_i_f failed\n"); abrt(); }
	if (i1 != 530908862) { printf("test_f_i_f failed\n"); abrt(); }
	if (f2 != 7687250.37932811f) { printf("test_f_i_f failed\n"); abrt(); }
	
} 
void test_d_i_f(double d0, int i1, float f2) { 
	if (d0 != 679983.441134730) { printf("test_d_i_f failed\n"); abrt(); }
	if (i1 != 722253655) { printf("test_d_i_f failed\n"); abrt(); }
	if (f2 != 6847163.15095873f) { printf("test_d_i_f failed\n"); abrt(); }
	
} 
void test_i_f_f(int i0, float f1, float f2) { 
	if (i0 != 1169798850) { printf("test_i_f_f failed\n"); abrt(); }
	if (f1 != 9073021.76507738f) { printf("test_i_f_f failed\n"); abrt(); }
	if (f2 != 3275835.37031082f) { printf("test_i_f_f failed\n"); abrt(); }
	
} 
void test_f_f_f(float f0, float f1, float f2) { 
	if (f0 != 297330.274928989f) { printf("test_f_f_f failed\n"); abrt(); }
	if (f1 != 3949640.49447893f) { printf("test_f_f_f failed\n"); abrt(); }
	if (f2 != 4978528.95625723f) { printf("test_f_f_f failed\n"); abrt(); }
	
} 
void test_d_f_f(double d0, float f1, float f2) { 
	if (d0 != 28320.10678780250) { printf("test_d_f_f failed\n"); abrt(); }
	if (f1 != 1573619.58183404f) { printf("test_d_f_f failed\n"); abrt(); }
	if (f2 != 7855158.84382875f) { printf("test_d_f_f failed\n"); abrt(); }
	
} 
void test_i_d_f(int i0, double d1, float f2) { 
	if (i0 != 2129156472) { printf("test_i_d_f failed\n"); abrt(); }
	if (d1 != 1158596.873166930) { printf("test_i_d_f failed\n"); abrt(); }
	if (f2 != 5440731.98332928f) { printf("test_i_d_f failed\n"); abrt(); }
	
} 
void test_f_d_f(float f0, double d1, float f2) { 
	if (f0 != 7796612.62548174f) { printf("test_f_d_f failed\n"); abrt(); }
	if (d1 != 9591242.921483990) { printf("test_f_d_f failed\n"); abrt(); }
	if (f2 != 9825156.09707967f) { printf("test_f_d_f failed\n"); abrt(); }
	
} 
void test_d_d_f(double d0, double d1, float f2) { 
	if (d0 != 7390610.988565280) { printf("test_d_d_f failed\n"); abrt(); }
	if (d1 != 4597875.632598520) { printf("test_d_d_f failed\n"); abrt(); }
	if (f2 != 8287172.69617339f) { printf("test_d_d_f failed\n"); abrt(); }
	
} 
void test_i_i_d(int i0, int i1, double d2) { 
	if (i0 != 1631643118) { printf("test_i_i_d failed\n"); abrt(); }
	if (i1 != 1160360112) { printf("test_i_i_d failed\n"); abrt(); }
	if (d2 != 8948951.694292330) { printf("test_i_i_d failed\n"); abrt(); }
	
} 
void test_f_i_d(float f0, int i1, double d2) { 
	if (f0 != 9455535.39020462f) { printf("test_f_i_d failed\n"); abrt(); }
	if (i1 != 1675613875) { printf("test_f_i_d failed\n"); abrt(); }
	if (d2 != 932819.3029074680) { printf("test_f_i_d failed\n"); abrt(); }
	
} 
void test_d_i_d(double d0, int i1, double d2) { 
	if (d0 != 4734731.523979290) { printf("test_d_i_d failed\n"); abrt(); }
	if (i1 != 2132199733) { printf("test_d_i_d failed\n"); abrt(); }
	if (d2 != 2029113.500477780) { printf("test_d_i_d failed\n"); abrt(); }
	
} 
void test_i_f_d(int i0, float f1, double d2) { 
	if (i0 != 265146546) { printf("test_i_f_d failed\n"); abrt(); }
	if (f1 != 7071953.98614928f) { printf("test_i_f_d failed\n"); abrt(); }
	if (d2 != 6199293.073631470) { printf("test_i_f_d failed\n"); abrt(); }
	
} 
void test_f_f_d(float f0, float f1, double d2) { 
	if (f0 != 4941205.66131095f) { printf("test_f_f_d failed\n"); abrt(); }
	if (f1 != 4091938.30418619f) { printf("test_f_f_d failed\n"); abrt(); }
	if (d2 != 4346785.969942740) { printf("test_f_f_d failed\n"); abrt(); }
	
} 
void test_d_f_d(double d0, float f1, double d2) { 
	if (d0 != 9869929.288482630) { printf("test_d_f_d failed\n"); abrt(); }
	if (f1 != 6673705.93056866f) { printf("test_d_f_d failed\n"); abrt(); }
	if (d2 != 9601799.091424720) { printf("test_d_f_d failed\n"); abrt(); }
	
} 
void test_i_d_d(int i0, double d1, double d2) { 
	if (i0 != 131452541) { printf("test_i_d_d failed\n"); abrt(); }
	if (d1 != 6261904.009016310) { printf("test_i_d_d failed\n"); abrt(); }
	if (d2 != 4823421.375162340) { printf("test_i_d_d failed\n"); abrt(); }
	
} 
void test_f_d_d(float f0, double d1, double d2) { 
	if (f0 != 5922414.41681725f) { printf("test_f_d_d failed\n"); abrt(); }
	if (d1 != 6702656.993337260) { printf("test_f_d_d failed\n"); abrt(); }
	if (d2 != 5607046.022487440) { printf("test_f_d_d failed\n"); abrt(); }
	
} 
void test_d_d_d(double d0, double d1, double d2) { 
	if (d0 != 5217952.403648450) { printf("test_d_d_d failed\n"); abrt(); }
	if (d1 != 1474960.200484540) { printf("test_d_d_d failed\n"); abrt(); }
	if (d2 != 6616697.012280920) { printf("test_d_d_d failed\n"); abrt(); }
	
} 
void test_i_i_i_i(int i0, int i1, int i2, int i3) { 
	if (i0 != 550711004) { printf("test_i_i_i_i failed\n"); abrt(); }
	if (i1 != 2049228450) { printf("test_i_i_i_i failed\n"); abrt(); }
	if (i2 != 660103513) { printf("test_i_i_i_i failed\n"); abrt(); }
	if (i3 != 1935473443) { printf("test_i_i_i_i failed\n"); abrt(); }
	
} 
void test_f_i_i_i(float f0, int i1, int i2, int i3) { 
	if (f0 != 3823510.4483071f) { printf("test_f_i_i_i failed\n"); abrt(); }
	if (i1 != 2085001596) { printf("test_f_i_i_i failed\n"); abrt(); }
	if (i2 != 346536540) { printf("test_f_i_i_i failed\n"); abrt(); }
	if (i3 != 246556340) { printf("test_f_i_i_i failed\n"); abrt(); }
	
} 
void test_d_i_i_i(double d0, int i1, int i2, int i3) { 
	if (d0 != 9169054.945526760) { printf("test_d_i_i_i failed\n"); abrt(); }
	if (i1 != 247158890) { printf("test_d_i_i_i failed\n"); abrt(); }
	if (i2 != 1365058957) { printf("test_d_i_i_i failed\n"); abrt(); }
	if (i3 != 1283095986) { printf("test_d_i_i_i failed\n"); abrt(); }
	
} 
void test_i_f_i_i(int i0, float f1, int i2, int i3) { 
	if (i0 != 428549463) { printf("test_i_f_i_i failed\n"); abrt(); }
	if (f1 != 6509395.18899925f) { printf("test_i_f_i_i failed\n"); abrt(); }
	if (i2 != 1803485695) { printf("test_i_f_i_i failed\n"); abrt(); }
	if (i3 != 1995086607) { printf("test_i_f_i_i failed\n"); abrt(); }
	
} 
void test_f_f_i_i(float f0, float f1, int i2, int i3) { 
	if (f0 != 6306887.59865304f) { printf("test_f_f_i_i failed\n"); abrt(); }
	if (f1 != 5355299.8767784f) { printf("test_f_f_i_i failed\n"); abrt(); }
	if (i2 != 2080777936) { printf("test_f_f_i_i failed\n"); abrt(); }
	if (i3 != 1579526223) { printf("test_f_f_i_i failed\n"); abrt(); }
	
} 
void test_d_f_i_i(double d0, float f1, int i2, int i3) { 
	if (d0 != 8694460.463466210) { printf("test_d_f_i_i failed\n"); abrt(); }
	if (f1 != 6455699.4226033f) { printf("test_d_f_i_i failed\n"); abrt(); }
	if (i2 != 1712543979) { printf("test_d_f_i_i failed\n"); abrt(); }
	if (i3 != 202113162) { printf("test_d_f_i_i failed\n"); abrt(); }
	
} 
void test_i_d_i_i(int i0, double d1, int i2, int i3) { 
	if (i0 != 570405119) { printf("test_i_d_i_i failed\n"); abrt(); }
	if (d1 != 4873164.064588810) { printf("test_i_d_i_i failed\n"); abrt(); }
	if (i2 != 82449272) { printf("test_i_d_i_i failed\n"); abrt(); }
	if (i3 != 1439285642) { printf("test_i_d_i_i failed\n"); abrt(); }
	
} 
void test_f_d_i_i(float f0, double d1, int i2, int i3) { 
	if (f0 != 5427319.63502444f) { printf("test_f_d_i_i failed\n"); abrt(); }
	if (d1 != 3988738.273651010) { printf("test_f_d_i_i failed\n"); abrt(); }
	if (i2 != 36646113) { printf("test_f_d_i_i failed\n"); abrt(); }
	if (i3 != 771886361) { printf("test_f_d_i_i failed\n"); abrt(); }
	
} 
void test_d_d_i_i(double d0, double d1, int i2, int i3) { 
	if (d0 != 2816025.77961930) { printf("test_d_d_i_i failed\n"); abrt(); }
	if (d1 != 895722.4993135780) { printf("test_d_d_i_i failed\n"); abrt(); }
	if (i2 != 1393066624) { printf("test_d_d_i_i failed\n"); abrt(); }
	if (i3 != 205380693) { printf("test_d_d_i_i failed\n"); abrt(); }
	
} 
void test_i_i_f_i(int i0, int i1, float f2, int i3) { 
	if (i0 != 1816047733) { printf("test_i_i_f_i failed\n"); abrt(); }
	if (i1 != 1063320101) { printf("test_i_i_f_i failed\n"); abrt(); }
	if (f2 != 6182695.5259993f) { printf("test_i_i_f_i failed\n"); abrt(); }
	if (i3 != 1318151993) { printf("test_i_i_f_i failed\n"); abrt(); }
	
} 
void test_f_i_f_i(float f0, int i1, float f2, int i3) { 
	if (f0 != 549238.036282951f) { printf("test_f_i_f_i failed\n"); abrt(); }
	if (i1 != 523205015) { printf("test_f_i_f_i failed\n"); abrt(); }
	if (f2 != 7732733.27663734f) { printf("test_f_i_f_i failed\n"); abrt(); }
	if (i3 != 1331249729) { printf("test_f_i_f_i failed\n"); abrt(); }
	
} 
void test_d_i_f_i(double d0, int i1, float f2, int i3) { 
	if (d0 != 1194765.063637070) { printf("test_d_i_f_i failed\n"); abrt(); }
	if (i1 != 643630142) { printf("test_d_i_f_i failed\n"); abrt(); }
	if (f2 != 9653263.81847621f) { printf("test_d_i_f_i failed\n"); abrt(); }
	if (i3 != 1788900390) { printf("test_d_i_f_i failed\n"); abrt(); }
	
} 
void test_i_f_f_i(int i0, float f1, float f2, int i3) { 
	if (i0 != 548833028) { printf("test_i_f_f_i failed\n"); abrt(); }
	if (f1 != 4996150.82041281f) { printf("test_i_f_f_i failed\n"); abrt(); }
	if (f2 != 1549676.05673594f) { printf("test_i_f_f_i failed\n"); abrt(); }
	if (i3 != 659744198) { printf("test_i_f_f_i failed\n"); abrt(); }
	
} 
void test_f_f_f_i(float f0, float f1, float f2, int i3) { 
	if (f0 != 6491942.96313549f) { printf("test_f_f_f_i failed\n"); abrt(); }
	if (f1 != 105729.465485993f) { printf("test_f_f_f_i failed\n"); abrt(); }
	if (f2 != 3425082.36570485f) { printf("test_f_f_f_i failed\n"); abrt(); }
	if (i3 != 1945349663) { printf("test_f_f_f_i failed\n"); abrt(); }
	
} 
void test_d_f_f_i(double d0, float f1, float f2, int i3) { 
	if (d0 != 3291294.496505620) { printf("test_d_f_f_i failed\n"); abrt(); }
	if (f1 != 1940131.44946148f) { printf("test_d_f_f_i failed\n"); abrt(); }
	if (f2 != 4521038.54378155f) { printf("test_d_f_f_i failed\n"); abrt(); }
	if (i3 != 1397021818) { printf("test_d_f_f_i failed\n"); abrt(); }
	
} 
void test_i_d_f_i(int i0, double d1, float f2, int i3) { 
	if (i0 != 734146058) { printf("test_i_d_f_i failed\n"); abrt(); }
	if (d1 != 7576314.354115040) { printf("test_i_d_f_i failed\n"); abrt(); }
	if (f2 != 3998679.51449057f) { printf("test_i_d_f_i failed\n"); abrt(); }
	if (i3 != 591823526) { printf("test_i_d_f_i failed\n"); abrt(); }
	
} 
void test_f_d_f_i(float f0, double d1, float f2, int i3) { 
	if (f0 != 8660516.87894892f) { printf("test_f_d_f_i failed\n"); abrt(); }
	if (d1 != 4253697.855671920) { printf("test_f_d_f_i failed\n"); abrt(); }
	if (f2 != 2716302.2866856f) { printf("test_f_d_f_i failed\n"); abrt(); }
	if (i3 != 1783423320) { printf("test_f_d_f_i failed\n"); abrt(); }
	
} 
void test_d_d_f_i(double d0, double d1, float f2, int i3) { 
	if (d0 != 4989235.318688930) { printf("test_d_d_f_i failed\n"); abrt(); }
	if (d1 != 44339.5100055710) { printf("test_d_d_f_i failed\n"); abrt(); }
	if (f2 != 4517333.2657679f) { printf("test_d_d_f_i failed\n"); abrt(); }
	if (i3 != 1590278330) { printf("test_d_d_f_i failed\n"); abrt(); }
	
} 
void test_i_i_d_i(int i0, int i1, double d2, int i3) { 
	if (i0 != 1135733512) { printf("test_i_i_d_i failed\n"); abrt(); }
	if (i1 != 1489528127) { printf("test_i_i_d_i failed\n"); abrt(); }
	if (d2 != 1390683.719172930) { printf("test_i_i_d_i failed\n"); abrt(); }
	if (i3 != 1692589819) { printf("test_i_i_d_i failed\n"); abrt(); }
	
} 
void test_f_i_d_i(float f0, int i1, double d2, int i3) { 
	if (f0 != 1682080.92230611f) { printf("test_f_i_d_i failed\n"); abrt(); }
	if (i1 != 1410297446) { printf("test_f_i_d_i failed\n"); abrt(); }
	if (d2 != 4965053.168616750) { printf("test_f_i_d_i failed\n"); abrt(); }
	if (i3 != 2033213217) { printf("test_f_i_d_i failed\n"); abrt(); }
	
} 
void test_d_i_d_i(double d0, int i1, double d2, int i3) { 
	if (d0 != 2518603.508949830) { printf("test_d_i_d_i failed\n"); abrt(); }
	if (i1 != 684837645) { printf("test_d_i_d_i failed\n"); abrt(); }
	if (d2 != 5692363.83364430) { printf("test_d_i_d_i failed\n"); abrt(); }
	if (i3 != 1277067745) { printf("test_d_i_d_i failed\n"); abrt(); }
	
} 
void test_i_f_d_i(int i0, float f1, double d2, int i3) { 
	if (i0 != 124880980) { printf("test_i_f_d_i failed\n"); abrt(); }
	if (f1 != 9628032.95480775f) { printf("test_i_f_d_i failed\n"); abrt(); }
	if (d2 != 5187028.11088520) { printf("test_i_f_d_i failed\n"); abrt(); }
	if (i3 != 160711332) { printf("test_i_f_d_i failed\n"); abrt(); }
	
} 
void test_f_f_d_i(float f0, float f1, double d2, int i3) { 
	if (f0 != 6279065.84145361f) { printf("test_f_f_d_i failed\n"); abrt(); }
	if (f1 != 769487.465948302f) { printf("test_f_f_d_i failed\n"); abrt(); }
	if (d2 != 9222243.566098350) { printf("test_f_f_d_i failed\n"); abrt(); }
	if (i3 != 1791283881) { printf("test_f_f_d_i failed\n"); abrt(); }
	
} 
void test_d_f_d_i(double d0, float f1, double d2, int i3) { 
	if (d0 != 1501029.717964110) { printf("test_d_f_d_i failed\n"); abrt(); }
	if (f1 != 5026606.10207109f) { printf("test_d_f_d_i failed\n"); abrt(); }
	if (d2 != 2328304.166574820) { printf("test_d_f_d_i failed\n"); abrt(); }
	if (i3 != 2090527816) { printf("test_d_f_d_i failed\n"); abrt(); }
	
} 
void test_i_d_d_i(int i0, double d1, double d2, int i3) { 
	if (i0 != 1618382431) { printf("test_i_d_d_i failed\n"); abrt(); }
	if (d1 != 8404823.343533610) { printf("test_i_d_d_i failed\n"); abrt(); }
	if (d2 != 6558590.614769490) { printf("test_i_d_d_i failed\n"); abrt(); }
	if (i3 != 504813652) { printf("test_i_d_d_i failed\n"); abrt(); }
	
} 
void test_f_d_d_i(float f0, double d1, double d2, int i3) { 
	if (f0 != 9541963.06299803f) { printf("test_f_d_d_i failed\n"); abrt(); }
	if (d1 != 3058318.897949240) { printf("test_f_d_d_i failed\n"); abrt(); }
	if (d2 != 9335284.785145070) { printf("test_f_d_d_i failed\n"); abrt(); }
	if (i3 != 1130637210) { printf("test_f_d_d_i failed\n"); abrt(); }
	
} 
void test_d_d_d_i(double d0, double d1, double d2, int i3) { 
	if (d0 != 3166443.913362360) { printf("test_d_d_d_i failed\n"); abrt(); }
	if (d1 != 4001493.931181060) { printf("test_d_d_d_i failed\n"); abrt(); }
	if (d2 != 9189021.540137820) { printf("test_d_d_d_i failed\n"); abrt(); }
	if (i3 != 1249526406) { printf("test_d_d_d_i failed\n"); abrt(); }
	
} 
void test_i_i_i_f(int i0, int i1, int i2, float f3) { 
	if (i0 != 1761123245) { printf("test_i_i_i_f failed\n"); abrt(); }
	if (i1 != 886015027) { printf("test_i_i_i_f failed\n"); abrt(); }
	if (i2 != 1133006731) { printf("test_i_i_i_f failed\n"); abrt(); }
	if (f3 != 3509236.45575037f) { printf("test_i_i_i_f failed\n"); abrt(); }
	
} 
void test_f_i_i_f(float f0, int i1, int i2, float f3) { 
	if (f0 != 3779165.81535285f) { printf("test_f_i_i_f failed\n"); abrt(); }
	if (i1 != 114462873) { printf("test_f_i_i_f failed\n"); abrt(); }
	if (i2 != 361816875) { printf("test_f_i_i_f failed\n"); abrt(); }
	if (f3 != 172457.428062103f) { printf("test_f_i_i_f failed\n"); abrt(); }
	
} 
void test_d_i_i_f(double d0, int i1, int i2, float f3) { 
	if (d0 != 8358859.986291060) { printf("test_d_i_i_f failed\n"); abrt(); }
	if (i1 != 2144257104) { printf("test_d_i_i_f failed\n"); abrt(); }
	if (i2 != 302518023) { printf("test_d_i_i_f failed\n"); abrt(); }
	if (f3 != 205892.894073969f) { printf("test_d_i_i_f failed\n"); abrt(); }
	
} 
void test_i_f_i_f(int i0, float f1, int i2, float f3) { 
	if (i0 != 272341339) { printf("test_i_f_i_f failed\n"); abrt(); }
	if (f1 != 9953539.70027217f) { printf("test_i_f_i_f failed\n"); abrt(); }
	if (i2 != 1376072957) { printf("test_i_f_i_f failed\n"); abrt(); }
	if (f3 != 2076878.22244537f) { printf("test_i_f_i_f failed\n"); abrt(); }
	
} 
void test_f_f_i_f(float f0, float f1, int i2, float f3) { 
	if (f0 != 6269833.28651942f) { printf("test_f_f_i_f failed\n"); abrt(); }
	if (f1 != 5195550.36142101f) { printf("test_f_f_i_f failed\n"); abrt(); }
	if (i2 != 1968268960) { printf("test_f_f_i_f failed\n"); abrt(); }
	if (f3 != 8844909.55122473f) { printf("test_f_f_i_f failed\n"); abrt(); }
	
} 
void test_d_f_i_f(double d0, float f1, int i2, float f3) { 
	if (d0 != 8687184.44897890) { printf("test_d_f_i_f failed\n"); abrt(); }
	if (f1 != 259654.940272966f) { printf("test_d_f_i_f failed\n"); abrt(); }
	if (i2 != 119662563) { printf("test_d_f_i_f failed\n"); abrt(); }
	if (f3 != 4843274.85561721f) { printf("test_d_f_i_f failed\n"); abrt(); }
	
} 
void test_i_d_i_f(int i0, double d1, int i2, float f3) { 
	if (i0 != 1720134220) { printf("test_i_d_i_f failed\n"); abrt(); }
	if (d1 != 2029190.537308310) { printf("test_i_d_i_f failed\n"); abrt(); }
	if (i2 != 1613754972) { printf("test_i_d_i_f failed\n"); abrt(); }
	if (f3 != 2069018.18020597f) { printf("test_i_d_i_f failed\n"); abrt(); }
	
} 
void test_f_d_i_f(float f0, double d1, int i2, float f3) { 
	if (f0 != 6419790.69080545f) { printf("test_f_d_i_f failed\n"); abrt(); }
	if (d1 != 5910456.254741730) { printf("test_f_d_i_f failed\n"); abrt(); }
	if (i2 != 1920803643) { printf("test_f_d_i_f failed\n"); abrt(); }
	if (f3 != 9956814.67616038f) { printf("test_f_d_i_f failed\n"); abrt(); }
	
} 
void test_d_d_i_f(double d0, double d1, int i2, float f3) { 
	if (d0 != 8759378.44312670) { printf("test_d_d_i_f failed\n"); abrt(); }
	if (d1 != 6080781.1063740) { printf("test_d_d_i_f failed\n"); abrt(); }
	if (i2 != 1616944583) { printf("test_d_d_i_f failed\n"); abrt(); }
	if (f3 != 7944794.10593723f) { printf("test_d_d_i_f failed\n"); abrt(); }
	
} 
void test_i_i_f_f(int i0, int i1, float f2, float f3) { 
	if (i0 != 333992706) { printf("test_i_i_f_f failed\n"); abrt(); }
	if (i1 != 1549786935) { printf("test_i_i_f_f failed\n"); abrt(); }
	if (f2 != 9526229.58238496f) { printf("test_i_i_f_f failed\n"); abrt(); }
	if (f3 != 1119905.22651638f) { printf("test_i_i_f_f failed\n"); abrt(); }
	
} 
void test_f_i_f_f(float f0, int i1, float f2, float f3) { 
	if (f0 != 2756642.97504118f) { printf("test_f_i_f_f failed\n"); abrt(); }
	if (i1 != 1962030780) { printf("test_f_i_f_f failed\n"); abrt(); }
	if (f2 != 1412443.18448276f) { printf("test_f_i_f_f failed\n"); abrt(); }
	if (f3 != 4954328.56230948f) { printf("test_f_i_f_f failed\n"); abrt(); }
	
} 
void test_d_i_f_f(double d0, int i1, float f2, float f3) { 
	if (d0 != 1882401.705208250) { printf("test_d_i_f_f failed\n"); abrt(); }
	if (i1 != 4910194) { printf("test_d_i_f_f failed\n"); abrt(); }
	if (f2 != 6431315.94797527f) { printf("test_d_i_f_f failed\n"); abrt(); }
	if (f3 != 8066236.15554116f) { printf("test_d_i_f_f failed\n"); abrt(); }
	
} 
void test_i_f_f_f(int i0, float f1, float f2, float f3) { 
	if (i0 != 816445439) { printf("test_i_f_f_f failed\n"); abrt(); }
	if (f1 != 470103.663719286f) { printf("test_i_f_f_f failed\n"); abrt(); }
	if (f2 != 1711467.57138633f) { printf("test_i_f_f_f failed\n"); abrt(); }
	if (f3 != 9567629.56012412f) { printf("test_i_f_f_f failed\n"); abrt(); }
	
} 
void test_f_f_f_f(float f0, float f1, float f2, float f3) { 
	if (f0 != 1978607.83674823f) { printf("test_f_f_f_f failed\n"); abrt(); }
	if (f1 != 3029887.0242958f) { printf("test_f_f_f_f failed\n"); abrt(); }
	if (f2 != 6983720.86265781f) { printf("test_f_f_f_f failed\n"); abrt(); }
	if (f3 != 5065077.24983521f) { printf("test_f_f_f_f failed\n"); abrt(); }
	
} 
void test_d_f_f_f(double d0, float f1, float f2, float f3) { 
	if (d0 != 6777489.021977030) { printf("test_d_f_f_f failed\n"); abrt(); }
	if (f1 != 7673002.62776622f) { printf("test_d_f_f_f failed\n"); abrt(); }
	if (f2 != 4013837.52685422f) { printf("test_d_f_f_f failed\n"); abrt(); }
	if (f3 != 8078185.36794699f) { printf("test_d_f_f_f failed\n"); abrt(); }
	
} 
void test_i_d_f_f(int i0, double d1, float f2, float f3) { 
	if (i0 != 1395552474) { printf("test_i_d_f_f failed\n"); abrt(); }
	if (d1 != 6447414.458535760) { printf("test_i_d_f_f failed\n"); abrt(); }
	if (f2 != 5055785.8764461f) { printf("test_i_d_f_f failed\n"); abrt(); }
	if (f3 != 9514086.97837934f) { printf("test_i_d_f_f failed\n"); abrt(); }
	
} 
void test_f_d_f_f(float f0, double d1, float f2, float f3) { 
	if (f0 != 7815892.87954784f) { printf("test_f_d_f_f failed\n"); abrt(); }
	if (d1 != 3363210.885600050) { printf("test_f_d_f_f failed\n"); abrt(); }
	if (f2 != 3013845.84213242f) { printf("test_f_d_f_f failed\n"); abrt(); }
	if (f3 != 18890.3129087237f) { printf("test_f_d_f_f failed\n"); abrt(); }
	
} 
void test_d_d_f_f(double d0, double d1, float f2, float f3) { 
	if (d0 != 4955532.182617870) { printf("test_d_d_f_f failed\n"); abrt(); }
	if (d1 != 2310777.225040040) { printf("test_d_d_f_f failed\n"); abrt(); }
	if (f2 != 2976534.70171301f) { printf("test_d_d_f_f failed\n"); abrt(); }
	if (f3 != 9309901.57000736f) { printf("test_d_d_f_f failed\n"); abrt(); }
	
} 
void test_i_i_d_f(int i0, int i1, double d2, float f3) { 
	if (i0 != 958402028) { printf("test_i_i_d_f failed\n"); abrt(); }
	if (i1 != 1005161588) { printf("test_i_i_d_f failed\n"); abrt(); }
	if (d2 != 7524785.491885280) { printf("test_i_i_d_f failed\n"); abrt(); }
	if (f3 != 3922798.23348261f) { printf("test_i_i_d_f failed\n"); abrt(); }
	
} 
void test_f_i_d_f(float f0, int i1, double d2, float f3) { 
	if (f0 != 3041330.21986498f) { printf("test_f_i_d_f failed\n"); abrt(); }
	if (i1 != 808312167) { printf("test_f_i_d_f failed\n"); abrt(); }
	if (d2 != 8176107.248015150) { printf("test_f_i_d_f failed\n"); abrt(); }
	if (f3 != 3789290.26824693f) { printf("test_f_i_d_f failed\n"); abrt(); }
	
} 
void test_d_i_d_f(double d0, int i1, double d2, float f3) { 
	if (d0 != 7469491.61806480) { printf("test_d_i_d_f failed\n"); abrt(); }
	if (i1 != 1791175958) { printf("test_d_i_d_f failed\n"); abrt(); }
	if (d2 != 4741930.15492080) { printf("test_d_i_d_f failed\n"); abrt(); }
	if (f3 != 7452934.54127122f) { printf("test_d_i_d_f failed\n"); abrt(); }
	
} 
void test_i_f_d_f(int i0, float f1, double d2, float f3) { 
	if (i0 != 1684541087) { printf("test_i_f_d_f failed\n"); abrt(); }
	if (f1 != 7883930.98832067f) { printf("test_i_f_d_f failed\n"); abrt(); }
	if (d2 != 8764567.512508030) { printf("test_i_f_d_f failed\n"); abrt(); }
	if (f3 != 1949678.03305985f) { printf("test_i_f_d_f failed\n"); abrt(); }
	
} 
void test_f_f_d_f(float f0, float f1, double d2, float f3) { 
	if (f0 != 2689767.80869178f) { printf("test_f_f_d_f failed\n"); abrt(); }
	if (f1 != 5202780.69826055f) { printf("test_f_f_d_f failed\n"); abrt(); }
	if (d2 != 7862038.248709840) { printf("test_f_f_d_f failed\n"); abrt(); }
	if (f3 != 2997663.47383311f) { printf("test_f_f_d_f failed\n"); abrt(); }
	
} 
void test_d_f_d_f(double d0, float f1, double d2, float f3) { 
	if (d0 != 8202419.938025930) { printf("test_d_f_d_f failed\n"); abrt(); }
	if (f1 != 4209002.23390383f) { printf("test_d_f_d_f failed\n"); abrt(); }
	if (d2 != 4323466.673608360) { printf("test_d_f_d_f failed\n"); abrt(); }
	if (f3 != 3386352.58401297f) { printf("test_d_f_d_f failed\n"); abrt(); }
	
} 
int main(int argc, char **argv) { 
	test_i(1550815723);
	test_f(4058403.25492562f);
	test_d(9389619.494705920);
	test_i_i(1331402918, 1133231918);
	test_f_i(20770.9938693768f, 1004363255);
	test_d_i(7042894.533779740, 1464748280);
	test_i_f(424304409, 948810.232965052f);
	test_f_f(9680162.75195147f, 1378646.09046108f);
	test_d_f(6523872.773048110, 9140482.21035497f);
	test_i_d(1964580763, 9066496.50046180);
	test_f_d(2961097.54242053f, 998549.4177676560);
	test_d_d(5387731.395467270, 7311544.642524450);
	test_i_i_i(1312114750, 1902236726, 1675655795);
	test_f_i_i(9160964.45566129f, 1406971490, 1028074056);
	test_d_i_i(1462254.723497050, 1107590144, 1053669743);
	test_i_f_i(211598425, 3069857.15856335f, 448726329);
	test_f_f_i(4814250.20289493f, 8393294.75790475f, 1638099258);
	test_d_f_i(4577402.351084920, 2056169.60008328f, 677791258);
	test_i_d_i(766396665, 4970507.369126020, 269079978);
	test_f_d_i(5164066.53669417f, 3738497.158861730, 1004182640);
	test_d_d_i(3339444.458641910, 813764.7216346620, 1516608368);
	test_i_i_f(1165667352, 1242328201, 4256874.75503832f);
	test_f_i_f(4994097.8691405f, 530908862, 7687250.37932811f);
	test_d_i_f(679983.441134730, 722253655, 6847163.15095873f);
	test_i_f_f(1169798850, 9073021.76507738f, 3275835.37031082f);
	test_f_f_f(297330.274928989f, 3949640.49447893f, 4978528.95625723f);
	test_d_f_f(28320.10678780250, 1573619.58183404f, 7855158.84382875f);
	test_i_d_f(2129156472, 1158596.873166930, 5440731.98332928f);
	test_f_d_f(7796612.62548174f, 9591242.921483990, 9825156.09707967f);
	test_d_d_f(7390610.988565280, 4597875.632598520, 8287172.69617339f);
	test_i_i_d(1631643118, 1160360112, 8948951.694292330);
	test_f_i_d(9455535.39020462f, 1675613875, 932819.3029074680);
	test_d_i_d(4734731.523979290, 2132199733, 2029113.500477780);
	test_i_f_d(265146546, 7071953.98614928f, 6199293.073631470);
	test_f_f_d(4941205.66131095f, 4091938.30418619f, 4346785.969942740);
	test_d_f_d(9869929.288482630, 6673705.93056866f, 9601799.091424720);
	test_i_d_d(131452541, 6261904.009016310, 4823421.375162340);
	test_f_d_d(5922414.41681725f, 6702656.993337260, 5607046.022487440);
	test_d_d_d(5217952.403648450, 1474960.200484540, 6616697.012280920);
	test_i_i_i_i(550711004, 2049228450, 660103513, 1935473443);
	test_f_i_i_i(3823510.4483071f, 2085001596, 346536540, 246556340);
	test_d_i_i_i(9169054.945526760, 247158890, 1365058957, 1283095986);
	test_i_f_i_i(428549463, 6509395.18899925f, 1803485695, 1995086607);
	test_f_f_i_i(6306887.59865304f, 5355299.8767784f, 2080777936, 1579526223);
	test_d_f_i_i(8694460.463466210, 6455699.4226033f, 1712543979, 202113162);
	test_i_d_i_i(570405119, 4873164.064588810, 82449272, 1439285642);
	test_f_d_i_i(5427319.63502444f, 3988738.273651010, 36646113, 771886361);
	test_d_d_i_i(2816025.77961930, 895722.4993135780, 1393066624, 205380693);
	test_i_i_f_i(1816047733, 1063320101, 6182695.5259993f, 1318151993);
	test_f_i_f_i(549238.036282951f, 523205015, 7732733.27663734f, 1331249729);
	test_d_i_f_i(1194765.063637070, 643630142, 9653263.81847621f, 1788900390);
	test_i_f_f_i(548833028, 4996150.82041281f, 1549676.05673594f, 659744198);
	test_f_f_f_i(6491942.96313549f, 105729.465485993f, 3425082.36570485f, 1945349663);
	test_d_f_f_i(3291294.496505620, 1940131.44946148f, 4521038.54378155f, 1397021818);
	test_i_d_f_i(734146058, 7576314.354115040, 3998679.51449057f, 591823526);
	test_f_d_f_i(8660516.87894892f, 4253697.855671920, 2716302.2866856f, 1783423320);
	test_d_d_f_i(4989235.318688930, 44339.5100055710, 4517333.2657679f, 1590278330);
	test_i_i_d_i(1135733512, 1489528127, 1390683.719172930, 1692589819);
	test_f_i_d_i(1682080.92230611f, 1410297446, 4965053.168616750, 2033213217);
	test_d_i_d_i(2518603.508949830, 684837645, 5692363.83364430, 1277067745);
	test_i_f_d_i(124880980, 9628032.95480775f, 5187028.11088520, 160711332);
	test_f_f_d_i(6279065.84145361f, 769487.465948302f, 9222243.566098350, 1791283881);
	test_d_f_d_i(1501029.717964110, 5026606.10207109f, 2328304.166574820, 2090527816);
	test_i_d_d_i(1618382431, 8404823.343533610, 6558590.614769490, 504813652);
	test_f_d_d_i(9541963.06299803f, 3058318.897949240, 9335284.785145070, 1130637210);
	test_d_d_d_i(3166443.913362360, 4001493.931181060, 9189021.540137820, 1249526406);
	test_i_i_i_f(1761123245, 886015027, 1133006731, 3509236.45575037f);
	test_f_i_i_f(3779165.81535285f, 114462873, 361816875, 172457.428062103f);
	test_d_i_i_f(8358859.986291060, 2144257104, 302518023, 205892.894073969f);
	test_i_f_i_f(272341339, 9953539.70027217f, 1376072957, 2076878.22244537f);
	test_f_f_i_f(6269833.28651942f, 5195550.36142101f, 1968268960, 8844909.55122473f);
	test_d_f_i_f(8687184.44897890, 259654.940272966f, 119662563, 4843274.85561721f);
	test_i_d_i_f(1720134220, 2029190.537308310, 1613754972, 2069018.18020597f);
	test_f_d_i_f(6419790.69080545f, 5910456.254741730, 1920803643, 9956814.67616038f);
	test_d_d_i_f(8759378.44312670, 6080781.1063740, 1616944583, 7944794.10593723f);
	test_i_i_f_f(333992706, 1549786935, 9526229.58238496f, 1119905.22651638f);
	test_f_i_f_f(2756642.97504118f, 1962030780, 1412443.18448276f, 4954328.56230948f);
	test_d_i_f_f(1882401.705208250, 4910194, 6431315.94797527f, 8066236.15554116f);
	test_i_f_f_f(816445439, 470103.663719286f, 1711467.57138633f, 9567629.56012412f);
	test_f_f_f_f(1978607.83674823f, 3029887.0242958f, 6983720.86265781f, 5065077.24983521f);
	test_d_f_f_f(6777489.021977030, 7673002.62776622f, 4013837.52685422f, 8078185.36794699f);
	test_i_d_f_f(1395552474, 6447414.458535760, 5055785.8764461f, 9514086.97837934f);
	test_f_d_f_f(7815892.87954784f, 3363210.885600050, 3013845.84213242f, 18890.3129087237f);
	test_d_d_f_f(4955532.182617870, 2310777.225040040, 2976534.70171301f, 9309901.57000736f);
	test_i_i_d_f(958402028, 1005161588, 7524785.491885280, 3922798.23348261f);
	test_f_i_d_f(3041330.21986498f, 808312167, 8176107.248015150, 3789290.26824693f);
	test_d_i_d_f(7469491.61806480, 1791175958, 4741930.15492080, 7452934.54127122f);
	test_i_f_d_f(1684541087, 7883930.98832067f, 8764567.512508030, 1949678.03305985f);
	test_f_f_d_f(2689767.80869178f, 5202780.69826055f, 7862038.248709840, 2997663.47383311f);
	test_d_f_d_f(8202419.938025930, 4209002.23390383f, 4323466.673608360, 3386352.58401297f);
}
