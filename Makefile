#============================================================================
# Common makefile for SMEE project (PPC604gnu version).
# Author: weimm(weimm@smee.com.cn)
# Date: 2009-06-25
#
# TARGET   := Ŀ���ļ�
# SOURCES  := Դ�����ļ��б�
# SRCDIRS  := Դ����Ŀ¼�б�
# CPPFLAGS := ����ѡ�����CFLAGS��CXXFLAGS��
# LDFLAGS  := ����ѡ��
# SRCEXTS  := �������ͣ�[.c]��[.cpp]��[.c .cpp]
#============================================================================



IS_EXECUTABLE = true


# C��������C++��������ɾ�������������
CC  := gcc
CXX := g++
RM  := rm -f
CP  := cp -f


# ��װĿ¼
INSTALLDIR := .


# Ŀ���ļ�
ifeq ($(IS_EXECUTABLE), true)
	TARGET  := $(INSTALLDIR)/Test.out
else
	TARGET  := $(INSTALLDIR)/Test.so
endif


#����Ŀ¼
SRCDIR  := .
SRCDIRS := $(SRCDIR)/lib $(SRCDIR)/demo
SOURCES := 

#������ļ�����
SRCEXTS := .c .cpp


#ͷ�ļ�Ŀ¼
INCDIRS += $(SRCDIR) ./include



#����ѡ�����CFLAGS����ר��C�ı���ѡ�CXXFLAGS����ר��C++�ı���ѡ�CPPFLAGS�������߹���
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

#����SOURCES��SRCDIRS���ɴ�����Դ�����б�Ŀ���ļ��б�
SRCS := $(SOURCES) $(foreach d, $(SRCDIRS), $(wildcard $(addprefix $(d)/*, $(SRCEXTS))))
OBJS := $(foreach x, $(SRCEXTS), $(patsubst %$(x), %.o, $(filter %$(x), $(SRCS))))
###DEPS := $(patsubst %.o, %.d, $(OBJS))

.PHONY: all install clean sit

#���롢���ӣ���׺����.c��$(CC)���룬������$(CXX)���룬��������SRCEXTS��ȡֵ
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

#��װ������װ��������ÿ�ձ��롢ɾ��
install:
	$(CP) $(TARGET) $(INSTALLDIR)

clean:
	$(RM) $(OBJS)
	$(RM) $(TARGET)

sit: clean all install
	

