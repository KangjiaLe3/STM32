#include "dht11.h"
#include "../../Core/Inc/main.h"
#include "../../Core/Inc/gpio.h"

// 微秒级延时函数（基于72MHz主频）
static void delay_us(uint32_t us) {
    uint32_t ticks = us * 72 / 4;  // 72MHz, 每个循环约4个时钟周期
    while(ticks--);
}

static void DHT11_SetOutput(void) {
    GPIOA->CRL &= ~(GPIO_CRL_CNF1 | GPIO_CRL_MODE1);
    GPIOA->CRL |= GPIO_CRL_MODE1_1;  // 推挽输出，2MHz
}

static void DHT11_SetInput(void) {
    GPIOA->CRL &= ~(GPIO_CRL_CNF1 | GPIO_CRL_MODE1);
    GPIOA->CRL |= GPIO_CRL_CNF1_0;  // 浮空输入
}

void DHT11_Init(void) {
    DHT11_SetOutput();
    GPIOA->BSRR = DHT11_PIN;
}

bool DHT11_Read(float *temperature, float *humidity) {
    uint8_t data[5] = {0};
    uint32_t timeout;

    // 1. 主机发送起始信号
    DHT11_SetOutput();
    GPIOA->BRR = DHT11_PIN;      // 拉低
    Delay_ms(18);                 // 至少18ms
    GPIOA->BSRR = DHT11_PIN;     // 拉高
    delay_us(30);                 // 等待20-40us
    DHT11_SetInput();

    // 2. 等待DHT11响应（拉低80us）
    timeout = 0;
    while((GPIOA->IDR & DHT11_PIN) && timeout < 10000) {
        timeout++;
        delay_us(1);
    }
    if(timeout >= 10000) return false;  // 超时

    // 3. 等待DHT11拉高（80us）
    timeout = 0;
    while(!(GPIOA->IDR & DHT11_PIN) && timeout < 10000) {
        timeout++;
        delay_us(1);
    }
    if(timeout >= 10000) return false;

    // 4. 等待DHT11准备发送数据（拉低50us）
    timeout = 0;
    while((GPIOA->IDR & DHT11_PIN) && timeout < 10000) {
        timeout++;
        delay_us(1);
    }
    if(timeout >= 10000) return false;

    // 5. 读取40位数据
    for(int i = 0; i < 40; i++) {
        // 等待数据位开始（拉低50us）
        timeout = 0;
        while(!(GPIOA->IDR & DHT11_PIN) && timeout < 10000) {
            timeout++;
            delay_us(1);
        }
        if(timeout >= 10000) return false;

        // 延时30us后判断数据位
        delay_us(30);

        if(GPIOA->IDR & DHT11_PIN) {
            // 高电平持续时间>30us，表示数据位为1
            data[i/8] |= (1 << (7 - i%8));
        }
        // 否则为0，不需要操作

        // 等待数据位结束
        timeout = 0;
        while((GPIOA->IDR & DHT11_PIN) && timeout < 10000) {
            timeout++;
            delay_us(1);
        }
        if(timeout >= 10000) return false;
    }

    // 6. 校验和验证
    if(data[4] != ((data[0] + data[1] + data[2] + data[3]) & 0xFF)) {
        return false;
    }

    // 7. 解析数据
    *humidity = data[0] + data[1] * 0.1f;
    *temperature = data[2] + data[3] * 0.1f;

    return true;
}
