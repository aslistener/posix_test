# cross compiler
#CROSS=aarch64-linux-gnu
# cc=$(CROSS)-gcc
# cxx=$(CROSS)-g++
# linker=$(CROSS)-ld

cc=gcc
cxx=g++
linker=gcc

includeflags=-I.
lflags=-g
ccflags=-g $(includeflags)

cpp_sources= $(wildcard *.cc)
c_sources = $(wildcard *.c)

cpp_objs=$(patsubst %.cc,%.o,$(cpp_sources) )
c_objs= $(patsubst %.c,%.o,$(c_sources) )
objs = $(patsubst %.cc,%.o,$(cpp_sources) )  $(patsubst %.c,%.o,$(c_sources) )

CC = g++

#CFLAGS =  -g $(atkcflags) $(gtkcflags) -z,max-page-size=65536
#CPPFLAGS =  -g $(atkcflags) $(gtkcflags) -z,max-page-size=65536

main: $(objs)
	$(cxx) -g $(lflags) -o main $(objs)


# main: $(c_objs) $(cpp_objs)
# 	$(cc)  -g -o main $(c_objs) $(cpp_objs) \
# 	  $(atklflags) $(gtklflags) $(x11lflags);

ifneq ("$(wildcard $(cpp_objs))", "")
$(cpp_objs): $(cpp_sources)
	-$(cxx) -c $(ccflags) $< -o $@
endif

ifneq ("$(wildcard $(c_objs))", "")
$(c_objs): $(c_sources)
	$(cxx) -c $(ccflags) $< -o $@
endif

print:
	@echo $(objs)

clean:
	-rm -f *.o main




