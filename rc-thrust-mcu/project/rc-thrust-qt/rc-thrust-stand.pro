# Created by and for Qt Creator This file was created for editing the project sources only.
# You may attempt to use it for building too, by modifying this file here.

#TARGET = rc-thrust-stand

HEADERS = \
    ../../library/CMSIS/Core/Include/cmsis_armcc.h \
    ../../library/CMSIS/Core/Include/cmsis_armclang.h \
    ../../library/CMSIS/Core/Include/cmsis_compiler.h \
    ../../library/CMSIS/Core/Include/cmsis_gcc.h \
    ../../library/CMSIS/Core/Include/cmsis_iccarm.h \
    ../../library/CMSIS/Core/Include/cmsis_version.h \
    ../../library/CMSIS/Core/Include/core_cm3.h \
    ../../library/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xb.h \
    ../../library/CMSIS/Device/ST/STM32F1xx/Include/stm32f1xx.h \
    ../../library/CMSIS/Device/ST/STM32F1xx/Include/system_stm32f1xx.h \
    ../../library/STM32F1xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h \
    ../../library/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal.h \
    ../../library/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_adc.h \
    ../../library/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_adc_ex.h \
    ../../library/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_cortex.h \
    ../../library/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_def.h \
    ../../library/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_dma.h \
    ../../library/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_dma_ex.h \
    ../../library/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_exti.h \
    ../../library/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_flash.h \
    ../../library/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_flash_ex.h \
    ../../library/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_gpio.h \
    ../../library/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_gpio_ex.h \
    ../../library/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_pwr.h \
    ../../library/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc.h \
    ../../library/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc_ex.h \
    ../../library/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_spi.h \
    ../../library/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_tim.h \
    ../../library/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_tim_ex.h \
    ../../source/driver/ILI9341/5x5_font.h \
    ../../source/driver/ILI9341/ILI9341.h \
    ../../source/driver/ILI9341/ILI9341_STM32_SPI.h \
    ../../source/global.h \
    ../../source/lcd_lib/lcd_font_typedef.h \
    ../../source/lcd_lib/lcd_lib.h \
    ../../source/lcd_lib/lcd_lib_private.h \
    ../../source/lcd_lib_config.h \
    ../../source/stm32f1xx_hal_conf.h \
    ../../source/stm32f1xx_it.h

SOURCES = \
    ../../library/CMSIS/Device/ST/STM32F1xx/Source/Templates/system_stm32f1xx.c \
    ../../library/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal.c \
    ../../library/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_adc.c \
    ../../library/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_adc_ex.c \
    ../../library/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_cortex.c \
    ../../library/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_dma.c \
    ../../library/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_exti.c \
    ../../library/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_flash.c \
    ../../library/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_flash_ex.c \
    ../../library/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio.c \
    ../../library/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio_ex.c \
    ../../library/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_pwr.c \
    ../../library/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc.c \
    ../../library/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc_ex.c \
    ../../library/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_spi.c \
    ../../library/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_tim.c \
    ../../library/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_tim_ex.c \
    ../../source/driver/ILI9341/ILI9341.c \
    ../../source/driver/ILI9341/ILI9341_STM32_SPI.c \
    ../../source/lcd_lib/lcd_font_6x8_mono.c \
    ../../source/lcd_lib/lcd_font_12x16_mono.c \
    ../../source/lcd_lib/lcd_font_h10.c \
    ../../source/lcd_lib/lcd_font_h10_bold.c \
    ../../source/lcd_lib/lcd_font_h12.c \
    ../../source/lcd_lib/lcd_font_h32.c \
    ../../source/lcd_lib/lcd_font_h48.c \
    ../../source/lcd_lib/lcd_lib.c \
    ../../source/lcd_lib/lcd_lib_font.c \
    ../../source/lcd_lib/lcd_lib_graph.c \
    ../../source/lcd_lib/portable/lcd_lib_graph_ILI9341.c \
    ../../source/main.c \
    ../../source/main.cpp \
    ../../source/stm32f1xx_hal_msp.c \
    ../../source/stm32f1xx_it.c

INCLUDEPATH = \
    ../../library/CMSIS/Core/Include \
    ../../library/CMSIS/Device/ST/STM32F1xx/Include \
    ../../library/STM32F1xx_HAL_Driver/Inc \
    ../../source \
    ../../source/driver/ILI9341 \
    ../../source/lcd_lib


#DEFINES = 

DISTFILES += \
    ../../source/startup_stm32f103xb.s

