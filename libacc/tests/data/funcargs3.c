void abrt() {
 *(int*)(0) = 1; 
}
void test_i_d_d_f(int i0, double d1, double d2, float f3) { 
	if (i0 != 1067656792) { printf("test_i_d_d_f failed\n"); abrt(); }
	if (d1 != 4800975.417257480) { printf("test_i_d_d_f failed\n"); abrt(); }
	if (d2 != 4026238.387855480) { printf("test_i_d_d_f failed\n"); abrt(); }
	if (f3 != 6712872.74558083f) { printf("test_i_d_d_f failed\n"); abrt(); }
	
} 
void test_f_d_d_f(float f0, double d1, double d2, float f3) { 
	if (f0 != 6868478.26781811f) { printf("test_f_d_d_f failed\n"); abrt(); }
	if (d1 != 9036292.735611580) { printf("test_f_d_d_f failed\n"); abrt(); }
	if (d2 != 4331120.86055960) { printf("test_f_d_d_f failed\n"); abrt(); }
	if (f3 != 1924688.30441101f) { printf("test_f_d_d_f failed\n"); abrt(); }
	
} 
void test_d_d_d_f(double d0, double d1, double d2, float f3) { 
	if (d0 != 5897172.557213080) { printf("test_d_d_d_f failed\n"); abrt(); }
	if (d1 != 2096873.8102480) { printf("test_d_d_d_f failed\n"); abrt(); }
	if (d2 != 1476982.301668850) { printf("test_d_d_d_f failed\n"); abrt(); }
	if (f3 != 3689503.42878136f) { printf("test_d_d_d_f failed\n"); abrt(); }
	
} 
void test_i_i_i_d(int i0, int i1, int i2, double d3) { 
	if (i0 != 1753239049) { printf("test_i_i_i_d failed\n"); abrt(); }
	if (i1 != 808243497) { printf("test_i_i_i_d failed\n"); abrt(); }
	if (i2 != 1470519749) { printf("test_i_i_i_d failed\n"); abrt(); }
	if (d3 != 9279235.15092260) { printf("test_i_i_i_d failed\n"); abrt(); }
	
} 
void test_f_i_i_d(float f0, int i1, int i2, double d3) { 
	if (f0 != 3762411.28651952f) { printf("test_f_i_i_d failed\n"); abrt(); }
	if (i1 != 1251113077) { printf("test_f_i_i_d failed\n"); abrt(); }
	if (i2 != 1246846050) { printf("test_f_i_i_d failed\n"); abrt(); }
	if (d3 != 4434718.521690540) { printf("test_f_i_i_d failed\n"); abrt(); }
	
} 
void test_d_i_i_d(double d0, int i1, int i2, double d3) { 
	if (d0 != 3367286.669168510) { printf("test_d_i_i_d failed\n"); abrt(); }
	if (i1 != 875970681) { printf("test_d_i_i_d failed\n"); abrt(); }
	if (i2 != 934870893) { printf("test_d_i_i_d failed\n"); abrt(); }
	if (d3 != 6237536.338230710) { printf("test_d_i_i_d failed\n"); abrt(); }
	
} 
void test_i_f_i_d(int i0, float f1, int i2, double d3) { 
	if (i0 != 1564098653) { printf("test_i_f_i_d failed\n"); abrt(); }
	if (f1 != 246801.53276428f) { printf("test_i_f_i_d failed\n"); abrt(); }
	if (i2 != 1120912390) { printf("test_i_f_i_d failed\n"); abrt(); }
	if (d3 != 8177269.28585230) { printf("test_i_f_i_d failed\n"); abrt(); }
	
} 
void test_f_f_i_d(float f0, float f1, int i2, double d3) { 
	if (f0 != 6201062.70721177f) { printf("test_f_f_i_d failed\n"); abrt(); }
	if (f1 != 5636647.06872594f) { printf("test_f_f_i_d failed\n"); abrt(); }
	if (i2 != 421797970) { printf("test_f_f_i_d failed\n"); abrt(); }
	if (d3 != 1845054.19323870) { printf("test_f_f_i_d failed\n"); abrt(); }
	
} 
void test_d_f_i_d(double d0, float f1, int i2, double d3) { 
	if (d0 != 4171657.103913270) { printf("test_d_f_i_d failed\n"); abrt(); }
	if (f1 != 9843558.17420017f) { printf("test_d_f_i_d failed\n"); abrt(); }
	if (i2 != 828328191) { printf("test_d_f_i_d failed\n"); abrt(); }
	if (d3 != 6642384.059594380) { printf("test_d_f_i_d failed\n"); abrt(); }
	
} 
void test_i_d_i_d(int i0, double d1, int i2, double d3) { 
	if (i0 != 533569162) { printf("test_i_d_i_d failed\n"); abrt(); }
	if (d1 != 1010669.110995860) { printf("test_i_d_i_d failed\n"); abrt(); }
	if (i2 != 1211287924) { printf("test_i_d_i_d failed\n"); abrt(); }
	if (d3 != 6858599.198363320) { printf("test_i_d_i_d failed\n"); abrt(); }
	
} 
void test_f_d_i_d(float f0, double d1, int i2, double d3) { 
	if (f0 != 1944390.47203883f) { printf("test_f_d_i_d failed\n"); abrt(); }
	if (d1 != 9589274.948510040) { printf("test_f_d_i_d failed\n"); abrt(); }
	if (i2 != 80688283) { printf("test_f_d_i_d failed\n"); abrt(); }
	if (d3 != 7888769.879751440) { printf("test_f_d_i_d failed\n"); abrt(); }
	
} 
void test_d_d_i_d(double d0, double d1, int i2, double d3) { 
	if (d0 != 1256104.219410720) { printf("test_d_d_i_d failed\n"); abrt(); }
	if (d1 != 2179667.636068460) { printf("test_d_d_i_d failed\n"); abrt(); }
	if (i2 != 957929538) { printf("test_d_d_i_d failed\n"); abrt(); }
	if (d3 != 6339172.868445930) { printf("test_d_d_i_d failed\n"); abrt(); }
	
} 
void test_i_i_f_d(int i0, int i1, float f2, double d3) { 
	if (i0 != 239950773) { printf("test_i_i_f_d failed\n"); abrt(); }
	if (i1 != 375208938) { printf("test_i_i_f_d failed\n"); abrt(); }
	if (f2 != 6246334.54967768f) { printf("test_i_i_f_d failed\n"); abrt(); }
	if (d3 != 3560082.868647070) { printf("test_i_i_f_d failed\n"); abrt(); }
	
} 
void test_f_i_f_d(float f0, int i1, float f2, double d3) { 
	if (f0 != 9493652.73175513f) { printf("test_f_i_f_d failed\n"); abrt(); }
	if (i1 != 551923564) { printf("test_f_i_f_d failed\n"); abrt(); }
	if (f2 != 1548115.98355341f) { printf("test_f_i_f_d failed\n"); abrt(); }
	if (d3 != 7671150.7308130) { printf("test_f_i_f_d failed\n"); abrt(); }
	
} 
void test_d_i_f_d(double d0, int i1, float f2, double d3) { 
	if (d0 != 274043.0515465770) { printf("test_d_i_f_d failed\n"); abrt(); }
	if (i1 != 830738929) { printf("test_d_i_f_d failed\n"); abrt(); }
	if (f2 != 4509312.40225021f) { printf("test_d_i_f_d failed\n"); abrt(); }
	if (d3 != 4475488.968365790) { printf("test_d_i_f_d failed\n"); abrt(); }
	
} 
void test_i_f_f_d(int i0, float f1, float f2, double d3) { 
	if (i0 != 1919200523) { printf("test_i_f_f_d failed\n"); abrt(); }
	if (f1 != 2775664.48570262f) { printf("test_i_f_f_d failed\n"); abrt(); }
	if (f2 != 2820789.95020758f) { printf("test_i_f_f_d failed\n"); abrt(); }
	if (d3 != 4523247.30301740) { printf("test_i_f_f_d failed\n"); abrt(); }
	
} 
void test_f_f_f_d(float f0, float f1, float f2, double d3) { 
	if (f0 != 8413104.7585954f) { printf("test_f_f_f_d failed\n"); abrt(); }
	if (f1 != 1638546.05716899f) { printf("test_f_f_f_d failed\n"); abrt(); }
	if (f2 != 5095390.57740557f) { printf("test_f_f_f_d failed\n"); abrt(); }
	if (d3 != 8868702.229346330) { printf("test_f_f_f_d failed\n"); abrt(); }
	
} 
void test_d_f_f_d(double d0, float f1, float f2, double d3) { 
	if (d0 != 1451302.607970570) { printf("test_d_f_f_d failed\n"); abrt(); }
	if (f1 != 4469395.61904877f) { printf("test_d_f_f_d failed\n"); abrt(); }
	if (f2 != 1375426.44613948f) { printf("test_d_f_f_d failed\n"); abrt(); }
	if (d3 != 4307720.587791550) { printf("test_d_f_f_d failed\n"); abrt(); }
	
} 
void test_i_d_f_d(int i0, double d1, float f2, double d3) { 
	if (i0 != 525425773) { printf("test_i_d_f_d failed\n"); abrt(); }
	if (d1 != 4532624.557422550) { printf("test_i_d_f_d failed\n"); abrt(); }
	if (f2 != 7244272.44918548f) { printf("test_i_d_f_d failed\n"); abrt(); }
	if (d3 != 4782153.485327430) { printf("test_i_d_f_d failed\n"); abrt(); }
	
} 
void test_f_d_f_d(float f0, double d1, float f2, double d3) { 
	if (f0 != 8877746.98109464f) { printf("test_f_d_f_d failed\n"); abrt(); }
	if (d1 != 7738126.684530970) { printf("test_f_d_f_d failed\n"); abrt(); }
	if (f2 != 8022133.15237626f) { printf("test_f_d_f_d failed\n"); abrt(); }
	if (d3 != 6547789.229743730) { printf("test_f_d_f_d failed\n"); abrt(); }
	
} 
void test_d_d_f_d(double d0, double d1, float f2, double d3) { 
	if (d0 != 6755537.562727450) { printf("test_d_d_f_d failed\n"); abrt(); }
	if (d1 != 1856941.845075610) { printf("test_d_d_f_d failed\n"); abrt(); }
	if (f2 != 3038214.10009352f) { printf("test_d_d_f_d failed\n"); abrt(); }
	if (d3 != 3132707.871677520) { printf("test_d_d_f_d failed\n"); abrt(); }
	
} 
void test_i_i_d_d(int i0, int i1, double d2, double d3) { 
	if (i0 != 940243893) { printf("test_i_i_d_d failed\n"); abrt(); }
	if (i1 != 1738324485) { printf("test_i_i_d_d failed\n"); abrt(); }
	if (d2 != 5254310.930485280) { printf("test_i_i_d_d failed\n"); abrt(); }
	if (d3 != 2229251.103328810) { printf("test_i_i_d_d failed\n"); abrt(); }
	
} 
void test_f_i_d_d(float f0, int i1, double d2, double d3) { 
	if (f0 != 7302094.59602786f) { printf("test_f_i_d_d failed\n"); abrt(); }
	if (i1 != 362391292) { printf("test_f_i_d_d failed\n"); abrt(); }
	if (d2 != 8617071.26332920) { printf("test_f_i_d_d failed\n"); abrt(); }
	if (d3 != 787615.2691393660) { printf("test_f_i_d_d failed\n"); abrt(); }
	
} 
void test_d_i_d_d(double d0, int i1, double d2, double d3) { 
	if (d0 != 4911199.816124250) { printf("test_d_i_d_d failed\n"); abrt(); }
	if (i1 != 163405204) { printf("test_d_i_d_d failed\n"); abrt(); }
	if (d2 != 2767961.97238870) { printf("test_d_i_d_d failed\n"); abrt(); }
	if (d3 != 9690807.726624650) { printf("test_d_i_d_d failed\n"); abrt(); }
	
} 
void test_i_f_d_d(int i0, float f1, double d2, double d3) { 
	if (i0 != 1065555632) { printf("test_i_f_d_d failed\n"); abrt(); }
	if (f1 != 5459668.94557303f) { printf("test_i_f_d_d failed\n"); abrt(); }
	if (d2 != 1252616.360847190) { printf("test_i_f_d_d failed\n"); abrt(); }
	if (d3 != 3624143.380020970) { printf("test_i_f_d_d failed\n"); abrt(); }
	
} 
void test_f_f_d_d(float f0, float f1, double d2, double d3) { 
	if (f0 != 8660317.93578397f) { printf("test_f_f_d_d failed\n"); abrt(); }
	if (f1 != 1464633.3759233f) { printf("test_f_f_d_d failed\n"); abrt(); }
	if (d2 != 7537320.047956410) { printf("test_f_f_d_d failed\n"); abrt(); }
	if (d3 != 898614.5204454490) { printf("test_f_f_d_d failed\n"); abrt(); }
	
} 
void test_d_f_d_d(double d0, float f1, double d2, double d3) { 
	if (d0 != 1453022.552737870) { printf("test_d_f_d_d failed\n"); abrt(); }
	if (f1 != 6519467.39008999f) { printf("test_d_f_d_d failed\n"); abrt(); }
	if (d2 != 1133749.172397990) { printf("test_d_f_d_d failed\n"); abrt(); }
	if (d3 != 7993608.768864110) { printf("test_d_f_d_d failed\n"); abrt(); }
	
} 
void test_i_d_d_d(int i0, double d1, double d2, double d3) { 
	if (i0 != 1502618021) { printf("test_i_d_d_d failed\n"); abrt(); }
	if (d1 != 4957546.463071410) { printf("test_i_d_d_d failed\n"); abrt(); }
	if (d2 != 408777.9480335390) { printf("test_i_d_d_d failed\n"); abrt(); }
	if (d3 != 3054092.557323140) { printf("test_i_d_d_d failed\n"); abrt(); }
	
} 
void test_f_d_d_d(float f0, double d1, double d2, double d3) { 
	if (f0 != 6527910.20356982f) { printf("test_f_d_d_d failed\n"); abrt(); }
	if (d1 != 1817033.457960590) { printf("test_f_d_d_d failed\n"); abrt(); }
	if (d2 != 6450552.795706310) { printf("test_f_d_d_d failed\n"); abrt(); }
	if (d3 != 5270286.824621590) { printf("test_f_d_d_d failed\n"); abrt(); }
	
} 
void test_d_d_d_d(double d0, double d1, double d2, double d3) { 
	if (d0 != 7864492.684861620) { printf("test_d_d_d_d failed\n"); abrt(); }
	if (d1 != 4735201.343507570) { printf("test_d_d_d_d failed\n"); abrt(); }
	if (d2 != 4192665.345558770) { printf("test_d_d_d_d failed\n"); abrt(); }
	if (d3 != 4400053.069888370) { printf("test_d_d_d_d failed\n"); abrt(); }
	
} 
int main(int argc, char **argv) { 
	test_i_d_d_f(1067656792, 4800975.417257480, 4026238.387855480, 6712872.74558083f);
	test_f_d_d_f(6868478.26781811f, 9036292.735611580, 4331120.86055960, 1924688.30441101f);
	test_d_d_d_f(5897172.557213080, 2096873.8102480, 1476982.301668850, 3689503.42878136f);
	test_i_i_i_d(1753239049, 808243497, 1470519749, 9279235.15092260);
	test_f_i_i_d(3762411.28651952f, 1251113077, 1246846050, 4434718.521690540);
	test_d_i_i_d(3367286.669168510, 875970681, 934870893, 6237536.338230710);
	test_i_f_i_d(1564098653, 246801.53276428f, 1120912390, 8177269.28585230);
	test_f_f_i_d(6201062.70721177f, 5636647.06872594f, 421797970, 1845054.19323870);
	test_d_f_i_d(4171657.103913270, 9843558.17420017f, 828328191, 6642384.059594380);
	test_i_d_i_d(533569162, 1010669.110995860, 1211287924, 6858599.198363320);
	test_f_d_i_d(1944390.47203883f, 9589274.948510040, 80688283, 7888769.879751440);
	test_d_d_i_d(1256104.219410720, 2179667.636068460, 957929538, 6339172.868445930);
	test_i_i_f_d(239950773, 375208938, 6246334.54967768f, 3560082.868647070);
	test_f_i_f_d(9493652.73175513f, 551923564, 1548115.98355341f, 7671150.7308130);
	test_d_i_f_d(274043.0515465770, 830738929, 4509312.40225021f, 4475488.968365790);
	test_i_f_f_d(1919200523, 2775664.48570262f, 2820789.95020758f, 4523247.30301740);
	test_f_f_f_d(8413104.7585954f, 1638546.05716899f, 5095390.57740557f, 8868702.229346330);
	test_d_f_f_d(1451302.607970570, 4469395.61904877f, 1375426.44613948f, 4307720.587791550);
	test_i_d_f_d(525425773, 4532624.557422550, 7244272.44918548f, 4782153.485327430);
	test_f_d_f_d(8877746.98109464f, 7738126.684530970, 8022133.15237626f, 6547789.229743730);
	test_d_d_f_d(6755537.562727450, 1856941.845075610, 3038214.10009352f, 3132707.871677520);
	test_i_i_d_d(940243893, 1738324485, 5254310.930485280, 2229251.103328810);
	test_f_i_d_d(7302094.59602786f, 362391292, 8617071.26332920, 787615.2691393660);
	test_d_i_d_d(4911199.816124250, 163405204, 2767961.97238870, 9690807.726624650);
	test_i_f_d_d(1065555632, 5459668.94557303f, 1252616.360847190, 3624143.380020970);
	test_f_f_d_d(8660317.93578397f, 1464633.3759233f, 7537320.047956410, 898614.5204454490);
	test_d_f_d_d(1453022.552737870, 6519467.39008999f, 1133749.172397990, 7993608.768864110);
	test_i_d_d_d(1502618021, 4957546.463071410, 408777.9480335390, 3054092.557323140);
	test_f_d_d_d(6527910.20356982f, 1817033.457960590, 6450552.795706310, 5270286.824621590);
	test_d_d_d_d(7864492.684861620, 4735201.343507570, 4192665.345558770, 4400053.069888370);

}
