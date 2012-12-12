#include <uart.h>
#include <circularbuffer.h>
#include <led.h>
#include <stdarg.h>
#include <stdio.h>

int8 initializeUart0(uint32 baudrate)
{
    UART0_POWER_ON();               // Turn on power to UART0
    UART0_ENABLE_CLK();             // Turn on UART0 peripheral clock
    
    UART0_CONFIGURE();              // 8 bits, no Parity, 1 Stop bit
    UART0_SET_DLAB();               // set Divisor Latch Accress Bit
    UART0_SET_BAUDRATE(baudrate);   // Set baud rate
    UART0_CLEAR_DLAB();
   
    UART0_ENABLE_PINS();            // Enable UART TXD and RXD Pins
    UART0_ENABLE_AND_RESET_FIFO();  // Enable and reset TX and RX FIFO
    
#if (USE_UART_BUFFER == 1)
    if (initializeCb(&uart0ReadBuffer, UART_READ_BUFFER_SIZE, sizeof(char)) == -1)      // Initialize circular read buffer
        return -1;
    
    if (initializeCb(&uart0WriteBuffer, UART_WRITE_BUFFER_SIZE, sizeof(char)) == -1)    //Initialize circular write buffer
        return -1;
    
    UART0_SET_RBR_AND_THRE_INTERRUPT();      // Set the Receiver Data Ready interrupt
    UART0_ENABLE_IRQ();             // Enable Uarts Interrupt
#endif
    
    return 0;
}

int8 initializeUart1(uint32 baudrate)
{
    UART1_POWER_ON();               // Turn on power to UART1
    UART1_ENABLE_CLK();             // Turn on UART1 peripheral clock
    
    UART1_CONFIGURE();              // 8 bits, no Parity, 1 Stop bit
    UART1_SET_DLAB();               // set Divisor Latch Accress Bit
    UART1_SET_BAUDRATE(baudrate);   // Set baud rate
    UART1_CLEAR_DLAB();
   
    UART1_ENABLE_PINS();            // Enable UART TXD and RXD Pins
    UART1_ENABLE_AND_RESET_FIFO();  // Enable and reset TX and RX FIFO
    
#if (USE_UART_BUFFER == 1)
    if (initializeCb(&uart1ReadBuffer, UART_READ_BUFFER_SIZE, sizeof(char)) == -1)      // Initialize circular read buffer
        return -1;
    
    if (initializeCb(&uart1WriteBuffer, UART_WRITE_BUFFER_SIZE, sizeof(char)) == -1)    //Initialize circular write buffer
        return -1;
    
    UART1_SET_RBR_AND_THRE_INTERRUPT();      // Set the Receiver Data Ready interrupt
    UART1_ENABLE_IRQ();             // Enable Uarts Interrupt
#endif
    
    return 0;
}

int8 initializeUart2(uint32 baudrate)
{
    UART2_POWER_ON();               // Turn on power to UART2
    UART2_ENABLE_CLK();             // Turn on UART2 peripheral clock
    
    UART2_CONFIGURE();              // 8 bits, no Parity, 1 Stop bit
    UART2_SET_DLAB();               // set Divisor Latch Accress Bit
    UART2_SET_BAUDRATE(baudrate);   // Set baud rate
    UART2_CLEAR_DLAB();
   
    UART2_ENABLE_PINS();            // Enable UART TXD and RXD Pins
    UART2_ENABLE_AND_RESET_FIFO();  // Enable and reset TX and RX FIFO
    
#if (USE_UART_BUFFER == 1)
    if (initializeCb(&uart2ReadBuffer, UART_READ_BUFFER_SIZE, sizeof(char)) == -1)      // Initialize circular read buffer
        return -1;
    
    if (initializeCb(&uart2WriteBuffer, UART_WRITE_BUFFER_SIZE, sizeof(char)) == -1)    //Initialize circular write buffer
        return -1;
    
    UART2_SET_RBR_AND_THRE_INTERRUPT();      // Set the Receiver Data Ready interrupt
    UART2_ENABLE_IRQ();             // Enable Uarts Interrupt
#endif
    
    return 0;
}

int8 initializeUart3(uint32 baudrate)
{
    UART3_POWER_ON();               // Turn on power to UART3
    UART3_ENABLE_CLK();             // Turn on UART3 peripheral clock
    
    UART3_CONFIGURE();              // 8 bits, no Parity, 1 Stop bit
    UART3_SET_DLAB();               // set Divisor Latch Accress Bit
    UART3_SET_BAUDRATE(baudrate);   // Set baud rate
    UART3_CLEAR_DLAB();
   
    UART3_ENABLE_PINS();            // Enable UART TXD and RXD Pins
    UART3_ENABLE_AND_RESET_FIFO();  // Enable and reset TX and RX FIFO
    
#if (USE_UART_BUFFER == 1)
    if (initializeCb(&uart3ReadBuffer, UART_READ_BUFFER_SIZE, sizeof(char)) == -1)      // Initialize circular read buffer
        return -1;
    
    if (initializeCb(&uart3WriteBuffer, UART_WRITE_BUFFER_SIZE, sizeof(char)) == -1)    //Initialize circular write buffer
        return -1;
    
    UART3_SET_RBR_AND_THRE_INTERRUPT();      // Set the Receiver Data Ready interrupt
    UART3_ENABLE_IRQ();             // Enable Uarts Interrupt
#endif
    
    return 0;
}

#if (USE_UART_BUFFER == 1)
void UART0_IRQHANDLER()
{
    char c;
    
    if (UART0_RBR_INTERRUPT_OCCURED())          // If the interrupt comes from RBR
    {
        c = UART0_READ_CHAR();                  // Read character and put it to the buffer, also disables interrupt
        putCb(&uart0ReadBuffer,(void*)(&c));
    }
    else                                        // Else interrupt comes from THRE or put function
    {
        if (getCb(&uart0WriteBuffer,&c) == 0)   // If data is available
            UART0_SET_CHAR(c);                  // Put data to the uart, disables interrupt
    }
}
#endif

#if (USE_UART_BUFFER == 1)
void UART1_IRQHANDLER()
{
    char c;
    
    if (UART1_RBR_INTERRUPT_OCCURED())          // If the interrupt comes from RBR
    {
        c = UART1_READ_CHAR();                  // Read character and put it to the buffer, also disables interrupt
        putCb(&uart1ReadBuffer,(void*)(&c));
    }
    else                                        // Else interrupt comes from THRE or put function
    {
        if (getCb(&uart1WriteBuffer,&c) == 0)   // If data is available
            UART1_SET_CHAR(c);                  // Put data to the uart, disables interrupt
    }
}
#endif

#if (USE_UART_BUFFER == 1)
void UART2_IRQHANDLER()
{
        char c;
    
    if (UART2_RBR_INTERRUPT_OCCURED())          // If the interrupt comes from RBR
    {
        c = UART2_READ_CHAR();                  // Read character and put it to the buffer, also disables interrupt
        putCb(&uart2ReadBuffer,(void*)(&c));
    }
    else                                        // Else interrupt comes from THRE or put function
    {
        if (getCb(&uart2WriteBuffer,&c) == 0)   // If data is available
            UART2_SET_CHAR(c);                  // Put data to the uart, disables interrupt
    }
}
#endif

#if (USE_UART_BUFFER == 1)
void UART3_IRQHANDLER()
{
    char c;
    
    if (UART3_RBR_INTERRUPT_OCCURED())          // If the interrupt comes from RBR
    {
        c = UART3_READ_CHAR();                  // Read character and put it to the buffer, also disables interrupt
        putCb(&uart3ReadBuffer,(void*)(&c));
    }
    else                                        // Else interrupt comes from THRE or put function
    {
        if (getCb(&uart3WriteBuffer,&c) == 0)   // If data is available
            UART3_SET_CHAR(c);                  // Put data to the uart, disables interrupt
    }
}
#endif

int8 putcharUart0(char c)
{
#if (USE_UART_BUFFER == 1)
    if (putCb(&uart0WriteBuffer, &c) == 0)
    {
        if (UART0_THR_EMPTY())         // If THR is empty, trigger an interrupt to write data to the UART
            UART0_SET_IRQS();
        
        return 0;
    }
    else 
        return -1;
#else
    while(!UART0_THR_EMPTY());         // Block until THR empty
    UART0_SET_CHAR(c);
    return 0;
#endif
}

int8 putcharUart1(char c)
{
#if (USE_UART_BUFFER == 1)
    if (putCb(&uart1WriteBuffer, &c) == 0)
    {
        if (UART1_THR_EMPTY())         // If THR is empty, trigger an interrupt to write data to the UART
            UART1_SET_IRQS();
        
        return 0;
    }
    else 
        return -1;
#else
    while(!UART1_THR_EMPTY());         // Block until THR empty
    UART1_SET_CHAR(c);
    return 0;
#endif
}

int8 putcharUart2(char c)
{
#if (USE_UART_BUFFER == 1)
    if (putCb(&uart2WriteBuffer, &c) == 0)
    {
        if (UART2_THR_EMPTY())         // If THR is empty, trigger an interrupt to write data to the UART
            UART2_SET_IRQS();
        
        return 0;
    }
    else 
        return -1;
#else
    while(!UART2_THR_EMPTY());         // Block until THR empty
    UART2_SET_CHAR(c);
    return 0;
#endif
}

int8 putcharUart3(char c)
{
#if (USE_UART_BUFFER == 1)
    if (putCb(&uart3WriteBuffer, &c) == 0)
    {
        if (UART3_THR_EMPTY())         // If THR is empty, trigger an interrupt to write data to the UART
            UART3_SET_IRQS();
        
        return 0;
    }
    else 
        return -1;
#else
    while(!UART3_THR_EMPTY());         // Block until THR empty
    UART3_SET_CHAR(c);
    return 0;
#endif
}

int8 getcharUart0(char *c)
{
#if (USE_UART_BUFFER == 1)
    return getCb(&uart0ReadBuffer,c);   // Read char from circular buffer
#else
    while( UART0_RBR_EMPTY() );         // Nothing received so just block 
    *c = UART0_READ_CHAR();             // Read Receiver buffer register
    return 0;
#endif
}

int8 getcharUart1(char *c)
{
#if (USE_UART_BUFFER == 1)
    return getCb(&uart1ReadBuffer,c);   // Read char from circular buffer
#else
    while( UART1_RBR_EMPTY() );         // Nothing received so just block 
    *c = UART1_READ_CHAR();             // Read Receiver buffer register
    return 0;
#endif
}

int8 getcharUart2(char *c)
{
#if (USE_UART_BUFFER == 1)
    return getCb(&uart2ReadBuffer,c);   // Read char from circular buffer
#else
    while( UART2_RBR_EMPTY() );         // Nothing received so just block 
    *c = UART2_READ_CHAR();             // Read Receiver buffer register
    return 0;
#endif
}

int8 getcharUart3(char *c)
{
#if (USE_UART_BUFFER == 1)
    return getCb(&uart3ReadBuffer,c);   // Read char from circular buffer
#else
    while( UART3_RBR_EMPTY() );         // Nothing received so just block 
    *c = UART3_READ_CHAR();             // Read Receiver buffer register
    return 0;
#endif
}

void printfUart0(char *format, ...)
{
    char buffer[256];
    
    va_list arg_ptr;
    uint8 i = 0;
    
    va_start(arg_ptr,format);
    vsprintf(buffer,format, arg_ptr);
    va_end(arg_ptr);
    
    while (buffer[i] != 0)      // Loop through until reach string's zero terminator
    {
        putcharUart0(buffer[i]);
        i++;
    }
}

void printfUart1(char *format, ...)
{
    char buffer[256];
    
    va_list arg_ptr;
    uint8 i = 0;
    
    va_start(arg_ptr,format);
    vsprintf(buffer,format, arg_ptr);
    va_end(arg_ptr);
    
    while (buffer[i] != 0)      // Loop through until reach string's zero terminator
    {
        putcharUart1(buffer[i]);
        i++;
    }
}

void printfUart2(char *format, ...)
{
    char buffer[256];
    
    va_list arg_ptr;
    uint8 i = 0;
    
    va_start(arg_ptr,format);
    vsprintf(buffer,format, arg_ptr);
    va_end(arg_ptr);
    
    while (buffer[i] != 0)      // Loop through until reach string's zero terminator
    {
        putcharUart2(buffer[i]);
        i++;
    }
}

void printfUart3(char *format, ...)
{
    char buffer[256];
    
    va_list arg_ptr;
    uint8 i = 0;
    
    va_start(arg_ptr,format);
    vsprintf(buffer,format, arg_ptr);
    va_end(arg_ptr);
    
    while (buffer[i] != 0)      // Loop through until reach string's zero terminator
    {
        putcharUart3(buffer[i]);
        i++;
    }
}