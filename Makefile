#============================================================================
# Common makefile for SMEE project (PPC604gnu version).
# Author: weimm(weimm@smee.com.cn)
# Date: 2009-06-25
#
# TARGET   := 目标文件
# SOURCES  := 源代码文件列表
# SRCDIRS  := 源代码目录列表
# CPPFLAGS := 编译选项（还有CFLAGS、CXXFLAGS）
# LDFLAGS  := 连接选项
# SRCEXTS  := 代码类型，[.c]、[.cpp]或[.c .cpp]
#============================================================================



IS_EXECUTABLE = true


# C编译器、C++编译器、删除命令、拷贝命令
CC  := gcc
CXX := g++
RM  := rm -f
CP  := cp -f


# 安装目录
INSTALLDIR := .


# 目标文件
ifeq ($(IS_EXECUTABLE), true)
	TARGET  := $(INSTALLDIR)/Test.out
else
	TARGET  := $(INSTALLDIR)/Test.so
endif


#代码目录
SRCDIR  := .
SRCDIRS := $(SRCDIR)/lib $(SRCDIR)/demo
SOURCES := 

#代码后文件类型
SRCEXTS := .c .cpp


#头文件目录
INCDIRS += $(SRCDIR) ./include



#编译选项，其中CFLAGS——专给C的编译选项，CXXFLAGS——专给C++的编译选项，CPPFLAGS——两者公用
CFLAGS   +=
CXXFLAGS +=
LDFLAGS  += 
ifneq ($(IS_EXECUTABLE), true)
CPPFLAGS += -fPIC
LDFLAGS  += -lnsl -shared
endif

CPPFLAGS += -O2 -DNDEBUG

CPPFLAGS += 

CPPFLAGS += -Wall $(addprefix -I, $(INCDIRS)) 

CPPFLAGS += 

#根据SOURCES和SRCDIRS生成待编译源代码列表及目标文件列表
SRCS := $(SOURCES) $(foreach d, $(SRCDIRS), $(wildcard $(addprefix $(d)/*, $(SRCEXTS))))
OBJS := $(foreach x, $(SRCEXTS), $(patsubst %$(x), %.o, $(filter %$(x), $(SRCS))))
###DEPS := $(patsubst %.o, %.d, $(OBJS))

.PHONY: all install clean sit

#编译、连接，后缀名是.c用$(CC)编译，否则用$(CXX)编译，连接依据SRCEXTS的取值
all: $(TARGET)

###%.d: %.c
###	$(CC) -MM -MD $(CPPFLAGS) $(CFLAGS) $<
###%.d: %.cpp
###	$(CC) -MM -MD $(CPPFLAGS) $(CXXFLAGS) $<
		
%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<
%.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

	
$(TARGET): $(OBJS)
ifeq ($(strip $(SRCEXTS)), .c)
	$(CC) $(LDFLAGS) -o $@ $^
else
	$(CXX) $(LDFLAGS) -o $@ $^
endif

###-include $(DEPS)

#安装、反安装、发布、每日编译、删除
install:
	$(CP) $(TARGET) $(INSTALLDIR)

clean:
	$(RM) $(OBJS)
	$(RM) $(TARGET)

sit: clean all install
	

