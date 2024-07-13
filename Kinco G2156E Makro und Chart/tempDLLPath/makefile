SHELL=C:\Windows\System32\cmd.exe
ifdef ARM
#CXX = "$(APPDIRPATH)/Compile/arm/bin/arm-linux-gnueabihf-g++.exe"
CXX = "$(APPDIRPATH)/Compile/arm_12.2/bin/arm-none-linux-gnueabihf-g++.exe"
PATH = $(APPDIRPATH)/Compile/arm_12.2/bin
CXXFLAGS = -fPIC -I. -s
LIBS = -lc -lm
WARNING = -Werror=return-type
TAR = $(MACRO).so
else
#CXX = "$(APPDIRPATH)/Compile/MinGW/bin/g++"
CXX = "$(APPDIRPATH)/Compile/MinGW_12.2/bin/g++"
PATH = $(APPDIRPATH)/Compile/MinGW_12.2/bin
CXXFLAGS = -I. -s
LIBS = -lwsock32
WARNING = -Werror=return-type
TAR = $(MACRO).dll
endif

LDFLAGS = -L../lib 


CSRC = $(wildcard *.c)
CPPSRC = $(wildcard *.cpp)
COBJS = $(patsubst %.c,%.o,$(CSRC))
CPPOBJS = $(patsubst %.cpp,%.o,$(CPPSRC))

.PHONY : all
all : $(TAR)

$(TAR):$(COBJS) $(CPPOBJS)
	@$(CXX) -shared $(CXXFLAGS) -o $@ $^ $(LDFLAGS) $(LIBS) 

$(COBJS):%.o:%.c
	@$(CXX) $(CXXFLAGS) $(WARNING) -c $< -o $@
		
$(CPPOBJS):%.o:%.cpp
	@$(CXX) $(CXXFLAGS) $(WARNING) -c $< -o $@
		
.PHONY : clean
clean:
	@del *.o
