cmake_minimum_required(VERSION 3.11)

# Variables regarding the AVR chip
# CPU, you can find the list here:
# https://gcc.gnu.org/onlinedocs/gcc/AVR-Options.html
set(MCU   atmega328p)
set(F_CPU 16000000UL)
set(BAUD  115200)
set(PORT /dev/ttyACM0)
# The programmer to use, read avrdude manual for list
set(PROG_TYPE arduino)


add_definitions(-DF_CPU=${F_CPU})

# Use AVR GCC toolchain
set(AVRCPP   avr-g++)
set(AVRC     avr-gcc)
set(AVRSTRIP avr-strip)
set(OBJCOPY  avr-objcopy)
set(OBJDUMP  avr-objdump)
set(AVRSIZE  avr-size)
set(AVRDUDE  avrdude)

# Sets the compiler
# Needs to come before the project function
set(CMAKE_SYSTEM_NAME  Generic)
set(CMAKE_CXX_COMPILER ${AVRCPP})
set(CMAKE_C_COMPILER   ${AVRC})
set(CMAKE_ASM_COMPILER   ${AVRC})

project (blink C CXX ASM)

# Important project paths
set(BASE_PATH    "${${PROJECT_NAME}_SOURCE_DIR}")
set(INC_PATH     "${BASE_PATH}/include")
set(SRC_PATH     "${BASE_PATH}/src")
set(LIB_DIR_PATH "${BASE_PATH}/lib")
set(3RD_PARTY_LIB_DIR_PATH "${BASE_PATH}/3rd_Party")

# Files to be compiled
file(GLOB SRC_FILES "${SRC_PATH}/*.cpp"
                    "${SRC_PATH}/*.cc"
                    "${SRC_PATH}/*.c"
                    "${SRC_PATH}/*.cxx"
                    "${SRC_PATH}/*.S"
                    "${SRC_PATH}/*.s"
                    "${SRC_PATH}/*.sx"
                    "${SRC_PATH}/*.asm")

set(LIB_SRC_FILES)
set(LIB_INC_PATH)
file(GLOB LIBRARIES "${LIB_DIR_PATH}/*")
foreach(subdir ${LIBRARIES})
    file(GLOB lib_files "${subdir}/*.cpp"
                        "${subdir}/*.cc"
                        "${subdir}/*.c"
                        "${subdir}/*.cxx"
                        "${subdir}/*.S"
                        "${subdir}/*.s"
                        "${subdir}/*.sx"
                        "${subdir}/*.asm")
    if(IS_DIRECTORY ${subdir})
        list(APPEND LIB_INC_PATH  "${subdir}")
    endif()
    list(APPEND LIB_SRC_FILES "${lib_files}")
endforeach()

# Include ioLibrary_Driver
set(IOLIBRARY_DIR "${3RD_PARTY_LIB_DIR_PATH}/ioLibrary_Driver/Ethernet/")
file(GLOB IOLIBRARY_SOURCES "${IOLIBRARY_DIR}/*.c"
                            "${IOLIBRARY_DIR}/W5100/*.c")

include_directories(${IOLIBRARY_DIR})
include_directories(${IOLIBRARY_DIR}/socket)

# Compiler flags
set(CSTANDARD "-std=gnu99")
set(CDEBUG    "-gstabs -g -ggdb")
set(CWARN     "-Wall -Wstrict-prototypes -Wl,--gc-sections -Wl,--relax")
set(CTUNING   "-funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums -ffunction-sections -fdata-sections")
set(COPT      "-Os -lm -lprintf_flt")
set(CMCU      "-mmcu=${MCU}")
set(CDEFS     "-DF_CPU=${F_CPU} -DBAUD=${BAUD}")

set(CFLAGS   "${CMCU} ${CDEBUG} ${CDEFS} ${COPT} ${CWARN} ${CSTANDARD} ${CTUNING}")
set(CXXFLAGS "${CMCU} ${CDEBUG} ${CDEFS} ${COPT} ${CTUNING}")

set(CMAKE_C_FLAGS   "${CFLAGS}")
set(CMAKE_CXX_FLAGS "${CXXFLAGS}")
set(CMAKE_ASM_FLAGS   "${CFLAGS}")

# Project setup
include_directories(${INC_PATH} ${LIB_INC_PATH})
add_executable(${PROJECT_NAME} ${SRC_FILES} ${LIB_SRC_FILES} ${IOLIBRARY_SOURCES})
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "${PROJECT_NAME}.elf")

# Compiling targets
add_custom_target(strip ALL     ${AVRSTRIP} "${PROJECT_NAME}.elf" DEPENDS ${PROJECT_NAME})
add_custom_target(hex   ALL     ${OBJCOPY} -R .eeprom -O ihex "${PROJECT_NAME}.elf" "${PROJECT_NAME}.hex" DEPENDS strip)
add_custom_target(eeprom        ${OBJCOPY} -j .eeprom --change-section-lma .eeprom=0 -O ihex "${PROJECT_NAME}.elf" "${PROJECT_NAME}.eeprom" DEPENDS strip)

add_custom_target(flash ${AVRDUDE} -v -v -v -c ${PROG_TYPE} -p ${MCU} -P ${PORT} -b${BAUD} -U flash:w:${PROJECT_NAME}.hex DEPENDS hex)


set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "${PROJECT_NAME}.hex;${PROJECT_NAME}.eeprom;${PROJECT_NAME}.lst")

