/*
 *	Project Owner	: TU Chemnitz
 *	Project Name	: ASE Tutorial Unit-1
 *	File Name		: main.c
 *	Author			: ASE Admin
 *  Created on		: 25 Feb 2024
 */

/* Includes ******************************************************************/
#include "init.h"         // 初始化函数头文件
#include "xpc56el.h"       // SPC56EL微控制器寄存器定义（包含SIU、ADC、PIT等）
#include "siu.h"           // SIU（系统集成单元）初始化函数声明


/* Global variables **********************************************************/

int counter_value = 0;
int count_direction = 0;

// 计数器值，用于Task 3的二进制计数
// 取值范围0-7（因为只有3个LED，只能显示3位二进制数）



/* ============================================================================
 * Task 1: 电位器控制LED
 * ============================================================================
 * 功能：当SW1开关打开时，旋转电位器(POT)，控制P、Rx、Tx三个LED的亮灭
 *
 * 原理：电位器输出0-4095的模拟值，我们将它分成3段：
 *   - 值在 0-1365 之间：只有P LED亮
 *   - 值在 1366-2730 之间：P + Rx LED亮
 *   - 值在 2731-4095 之间：P + Rx + Tx 全亮
 *
 * @param value - 电位器的当前值（0-4095）
 */
void task_pot(int value){
    // 计算每个LED应该亮还是灭
    // threshold_1 = 4096 / 3 ≈ 1365
    uint8_t p_led  = (value > 683) ? 1 : 0;   // P LED是否亮
    uint8_t rx_led = (value > 1365) ? 1 : 0;   // Rx LED是否亮
    uint8_t tx_led = (value > 2730) ? 1 : 0;   // Tx LED是否亮（其实4095是最大值，这个条件永远不会满足）



    // 通过GPDO寄存器控制LED输出
    // GPDO[56]对应P LED，GPDO[57]对应Rx LED，GPDO[58]对应Tx LED
    // B.PDO表示取寄存器中的PDO位（Pad Data Out）
    SIU.GPDO[56].B.PDO = p_led;   // 控制P LED
    SIU.GPDO[57].B.PDO = rx_led;  // 控制Rx LED
    SIU.GPDO[58].B.PDO = tx_led;  // 控制Tx LED
}


/* ============================================================================
 * Task 2: 光敏电阻控制LED
 * ============================================================================
 * 功能：当SW1关闭、SW2打开时，光敏电阻(LDR)控制全部6个LED
 *
 * 原理：光敏电阻输出0-4095的值
 *   - 黑暗时：值接近4095
 *   - 明亮时：值接近0
 * 我们设定阈值2048（中间值）：
 *   - 值 > 2048（黑暗）→ 6个LED全亮
 *   - 值 <= 2048（明亮）→ 6个LED全灭
 *
 * @param value - 光敏电阻的当前值（0-4095）
 */
void task_ldr(int value){
    // 设定阈值为中间值2048（用int避免溢出）
    int threshold = 2048;

    // 判断所有LED应该亮还是灭
    uint8_t p_led  = (value > threshold) ? 1 : 0;
    uint8_t rx_led = (value > threshold) ? 1 : 0;
    uint8_t tx_led = (value > threshold) ? 1 : 0;
    uint8_t u1_led = (value > threshold) ? 1 : 0;
    uint8_t u2_led = (value > threshold) ? 1 : 0;
    uint8_t u3_led = (value > threshold) ? 1 : 0;

    // 控制6个LED全部输出
    SIU.GPDO[56].B.PDO = p_led;   // P LED
    SIU.GPDO[57].B.PDO = rx_led;  // Rx LED
    SIU.GPDO[58].B.PDO = tx_led;  // Tx LED
    SIU.GPDO[59].B.PDO = u1_led;  // U1 LED
    SIU.GPDO[43].B.PDO = u2_led;  // U2 LED
    SIU.GPDO[6].B.PDO  = u3_led;  // U3 LED
}


/* ============================================================================
 * Task 3: 二进制计数器
 * ============================================================================
 * 功能：当SW1和SW2关闭、SW3打开时，用U1、U2、U3显示二进制计数器
 *
 * 原理：用3个LED表示3位二进制数
 *   counter_value = 0 → U1=0, U2=0, U3=0 → 二进制: 000
 *   counter_value = 1 → U1=1, U2=0, U3=0 → 二进制: 001
 *   counter_value = 2 → U1=0, U2=1, U3=0 → 二进制: 010
 *   counter_value = 3 → U1=1, U2=1, U3=0 → 二进制: 011
 *   counter_value = 4 → U1=0, U2=0, U3=1 → 二进制: 100
 *   ... 以此类推到7，然后循环回0
 *
 * 注意：这个函数只负责显示计数器当前值
 *       计数器的递增是在PIT_Channel_1()中断中完成的
 */
void task_counter(void){
    // 右移操作取出每一位
    // (counter_value >> 0) & 1 取出最低位（U1）
    // (counter_value >> 1) & 1 取出第二位（U2）
    // (counter_value >> 2) & 1 取出第三位（U3）
    SIU.GPDO[59].B.PDO = (counter_value >> 0) & 1;  // U1 LED（最低位）
    SIU.GPDO[43].B.PDO = (counter_value >> 1) & 1;  // U2 LED（第二位）
    SIU.GPDO[6].B.PDO  = (counter_value >> 2) & 1;  // U3 LED（最高位）
}


/* ============================================================================
 * 辅助函数：读取开关状态
 * ============================================================================
 * 功能：读取指定开关的当前状态（打开或关闭）
 *
 * 开关在前面板上的位置和对应的引脚：
 *   SW1 → D[4] → PCR[52] → GPDI[52]
 *   SW2 → D[5] → PCR[53] → GPDI[53]
 *   SW3 → D[6] → PCR[54] → GPDI[54]
 *   SW4 → D[7] → PCR[55] → GPDI[55]
 *
 * @param sw_num - 开关编号（1-4）
 * @return 开关状态（1=打开, 0=关闭）
 */
uint8_t read_switch(uint8_t sw_num){
    // 根据开关编号返回对应的GPDI寄存器值
    if (sw_num == 1) return SIU.GPDI[52].R;  // 读取SW1
    if (sw_num == 2) return SIU.GPDI[53].R;  // 读取SW2
    if (sw_num == 3) return SIU.GPDI[54].R;  // 读取SW3
    if (sw_num == 4) return SIU.GPDI[55].R;  // 读取SW4
    return 0;  // 无效的开关编号
}


/* ============================================================================
 * 辅助函数：读取按钮状态
 * ============================================================================
 * 功能：读取指定按钮的当前状态（按下或松开）
 *
 * 按钮在前面板上的位置和对应的引脚：
 *   BT1 → D[12] → PCR[60] → GPDI[60]
 *   BT2 → D[14] → PCR[62] → GPDI[62]
 *
 * 注意：按钮按下时返回1，松开时返回0
 *
 * @param bt_num - 按钮编号（1-2）
 * @return 按钮状态（1=按下, 0=松开）
 */
uint8_t read_button(uint8_t bt_num){
    // 根据按钮编号返回对应的GPDI寄存器值
    if (bt_num == 1) return SIU.GPDI[60].R;  // 读取BT1
    if (bt_num == 2) return SIU.GPDI[62].R;  // 读取BT2
    return 0;  // 无效的按钮编号
}


/* ============================================================================
 * 主函数入口
 * ============================================================================
 * 这是程序的入口点，类似于普通C程序的main()函数
 */
int main(void) {
    /* peripheralsInit() - 初始化所有外设（ADC、PIT、SIU等）
     * 这个函数会配置所有需要的引脚，由模板提供，不要删除 */
    peripheralsInit();


    /* 配置并启动定时器（PIT通道1）
     * PIT_ConfigureTimer(通道号, 间隔毫秒)
     * 这里设置通道1，间隔1000ms = 1秒
     * 定时器每1秒会触发一次中断，执行PIT_Channel_1()函数 */
    PIT_ConfigureTimer(1, 1000);  // 配置PIT通道1，1秒间隔
    PIT_StartTimer(1);           // 启动PIT通道1定时器


    /* 主循环 - 程序会一直在这里运行 */
    while(1){
        /* systemFunction() - 系统内部函数
         * 由模板提供，负责ADC转换和LED闪烁，不要删除 */
        systemFunction();


        /* ========== 读取开关状态 ========== */
        // 判断当前哪些开关是打开的，用于决定执行哪个任务
        uint8_t sw1 = read_switch(1);  // SW1状态
        uint8_t sw2 = read_switch(2);  // SW2状态
        uint8_t sw3 = read_switch(3);  // SW3状态
        uint8_t sw4 = read_switch(4);  // SW4状态（控制计数器是否计数）


        /* ========== 读取传感器ADC值 ========== */
        // ADC转换后的值是12位的（0-4095）
        // ADC0.CDR[5] - 电位器(POT)的值，连接在ADC0的第5通道
        int pot_value = ADC0.CDR[5].R & 0x00000FFF;  // 读取电位器值（0-4095）

        // ADC1.CDR[3] - 光敏电阻(LDR)的值，连接在ADC1的第3通道
        int ldr_value = ADC1.CDR[3].R & 0x00000FFF;  // 读取光敏电阻值（0-4095）


        /* ========== 根据开关状态选择任务 ========== */
        /*
         * 任务选择逻辑（根据PDF描述）：
         *   SW1=ON              → Task 1（电位器控制LED）
         *   SW1=OFF, SW2=ON     → Task 2（光敏电阻控制LED）
         *   SW1=OFF, SW2=OFF, SW3=ON → Task 3（二进制计数器）
         *   其他情况             → 所有LED关闭
         */
        if (sw1 == 1) {
            // SW1打开，执行Task 1：电位器控制P/Rx/Tx LED
            task_pot(pot_value);
        }
        else if (sw2 == 1) {
            // SW2打开，执行Task 2：光敏电阻控制全部6个LED
            task_ldr(ldr_value);
        }
        else if (sw3 == 1) {
            // SW3打开，执行Task 3：二进制计数器（显示在U1/U2/U3）
            task_counter();
        }
        else {
            // 没有任务激活，关闭所有LED
            SIU.GPDO[56].B.PDO = 0;  // P LED关闭
            SIU.GPDO[57].B.PDO = 0;  // Rx LED关闭
            SIU.GPDO[58].B.PDO = 0;  // Tx LED关闭
            SIU.GPDO[59].B.PDO = 0;  // U1 LED关闭
            SIU.GPDO[43].B.PDO = 0;  // U2 LED关闭
            SIU.GPDO[6].B.PDO  = 0;  // U3 LED关闭
        }


        /* 10ms系统延时
         * 这个延时让主循环不要跑得太快，给系统一些响应时间
         * 同时也防止CPU全速运行导致过热 */
        osalThreadDelayMilliseconds(10UL);  // 延时10毫秒
    }
}


/* ============================================================================
 * PIT定时器通道1中断处理函数
 * ============================================================================
 * 功能：每秒钟被调用一次（由main中配置的1秒定时器触发）
 *       如果SW4打开，则计数器递增
 *
 * 触发条件：在main()中配置了PIT_ConfigureTimer(1, 1000)
 *           每隔1000毫秒（1秒），CPU会自动调用这个函数
 *
 * 注意：这是"中断"，意味着它会在主循环运行过程中被"打断"执行
 */
void PIT_Channel_1(void){
    // 检查SW4是否打开
    // SW4=ON → 计数器递增
    // SW4=OFF → 计数器保持不变（停止计数）
	static int last_bt1_state = 0;
	int bt1_state  = read_button(1);

	if (bt1_state == 1 && last_bt1_state == 0){
		count_direction = !count_direction;

	}

	last_bt1_state = bt1_state;

    if (read_switch(4) == 1) {
    	if(count_direction == 0){
    		counter_value = (counter_value + 1) % 8;
    	}
    	else{
    		counter_value = (counter_value - 1 + 8) % 8;
    	}
        // counter_value从0数到7，然后回到0（模8运算）
        // 等价于: counter_value = counter_value + 1; if(counter_value > 7) counter_value = 0;

    }
}


/* ============================================================================
 * PIT定时器通道2中断处理函数（暂未使用）
 * ============================================================================
 * 如果需要额外的定时任务，可以在这里实现
 */
void PIT_Channel_2(void){
    /* TO-DO: 在这里实现你的任务 */
}


/* ============================================================================
 * PIT定时器通道3中断处理函数（暂未使用）
 * ============================================================================
 * 如果需要额外的定时任务，可以在这里实现
 */
void PIT_Channel_3(void){
    /* TO-DO: 在这里实现你的任务 */
}
