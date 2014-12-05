#include <stdio.h>

extern unsigned int fast_hotplug_enabled;

extern unsigned int boost_duration;
extern unsigned int threshold_to_boost;
extern unsigned int screen_off_singlecore;

extern unsigned int idle_threshold;
extern unsigned int max_cpu_on;
extern unsigned int min_cpu_on;

extern unsigned int plug_in_core_1_threshold;
extern unsigned int plug_in_core_2_threshold;
extern unsigned int plug_in_core_3_threshold;
extern unsigned int plug_in_core_1_delay;
extern unsigned int plug_in_core_2_delay;
extern unsigned int plug_in_core_3_delay;

extern unsigned int plug_out_core_1_threshold;
extern unsigned int plug_out_core_2_threshold;
extern unsigned int plug_out_core_3_threshold;
extern unsigned int plug_out_core_1_delay;
extern unsigned int plug_out_core_3_delay;
extern unsigned int plug_out_core_2_delay;


void print_menu(){
	system("clear");
	printf("===============================================================\n");
	if(!min_cpu_on && !max_cpu_on && !fast_hotplug_enabled){
		printf("=                      Device not found                       =\n");
		printf("===============================================================\n");
	} else if(fast_hotplug_enabled){
		printf("=                    Fast Hotplug Enabled                     =\n");
		printf("===============================================================\n");
		printf("=  0) Disable fast hotplug                                    =\n");
		printf("= On screen on :                                              =\n");
		printf("=  1) * Min cpu on : %-10d * Max cpu on : %-15d=\n", min_cpu_on, max_cpu_on);
		printf("=  2) * Boost duration : %-6d * Threshold to boost : %-7d=\n", boost_duration, threshold_to_boost);
		printf("=  3) Plug in :                                               =\n");
		printf("=     * Cpu1 Threshold : %-7d* Cpu1 Delay : %-15d=\n", plug_in_core_1_threshold, plug_in_core_1_delay);
		printf("=     * Cpu2 Threshold : %-7d* Cpu2 Delay : %-15d=\n", plug_in_core_2_threshold, plug_in_core_2_delay);
		printf("=     * Cpu3 Threshold : %-7d* Cpu3 Delay : %-15d=\n", plug_in_core_3_threshold, plug_in_core_3_delay);
		printf("=  4) Plug out :                                              =\n");
		printf("=     * Cpu1 Threshold : %-7d* Cpu1 Delay : %-15d=\n", plug_out_core_1_threshold, plug_out_core_1_delay);
		printf("=     * Cpu2 Threshold : %-7d* Cpu2 Delay : %-15d=\n", plug_out_core_2_threshold, plug_out_core_2_delay);
		printf("=     * Cpu3 Threshold : %-7d* Cpu3 Delay : %-15d=\n", plug_out_core_3_threshold, plug_out_core_3_delay);
		printf("=  5) Idle threshold : %-39d=\n", idle_threshold);
		printf("= On screen off :                                             =\n");
		printf("=  6) Screen off singlecore : %-32d=\n", screen_off_singlecore);
	} else {
		printf("=                    Fast Hotplug Disabled                    =\n");
		printf("===============================================================\n");
		printf("=  0) Enable fast hotplug                                     =\n");
	}
		printf("=                                                             =\n");
		printf("=  7) Refresh                                                 =\n");
		printf("=  8) Quit                                                    =\n");
	printf("===============================================================\n\n");
	printf("Choose an option : ");
}
