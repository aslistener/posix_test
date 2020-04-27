# cross compiler
#CROSS=aarch64-linux-gnu
# cc=$(CROSS)-gcc
# cxx=$(CROSS)-g++
# linker=$(CROSS)-ld

cc=gcc
cxx=g++
linker=gcc

includeflags=-I.
lflags=-lc -lpthread
ccflags=-g $(includeflags)

cpp_sources= $(wildcard *.cc)
c_sources = $(wildcard *.c)

cpp_objs=$(patsubst %.cc,%.o,$(cpp_sources) )
c_objs= $(patsubst %.c,%.o,$(c_sources) )
objs = $(cpp_objs) $(c_objs)

CC = g++

#CFLAGS =  -g $(atkcflags) $(gtkcflags) -z,max-page-size=65536
#CPPFLAGS =  -g $(atkcflags) $(gtkcflags) -z,max-page-size=65536

main: $(objs)
	-@echo "linking  $(objs)"
	$(cxx) $(ccflags) $(cpp_sources) -o main $(lflags)

# main: $(c_objs) $(cpp_objs)
# 	$(cc)  -g -o main $(c_objs) $(cpp_objs) \
# 	  $(atklflags) $(gtklflags) $(x11lflags);

# check cpp files exist
# ifneq ("$(wildcard $(cpp_sources))", "")
# endif

# $(objs): %.o: %.cc
# 	echo "begin to compile cpp files: $(cpp_sources)"
# 	$(cxx) -c $(ccflags) $< -o $@

# # check c files exist
# ifneq ("$(wildcard $(c_sources))", "")
# $(c_objs): $(c_sources)
# 	$(cxx) -c $(ccflags) $< -o $@
# endif

print:
	@echo $(objs)

clean:
	-rm -f *.o main




