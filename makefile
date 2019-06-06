# Basic makefile for gpiorca project
# Creates a build folder where the final binary will be.
# Creates an obj directory in the build folder where the 
# *.o files will be placed during build

vpath %.c src
vpath %.h src

CXX := gcc
LXX = gcc

CXXFLAGS := -g -Isrc -c
LXXFLAGS := -g 

BUILDDIR := build
SRCDIR := src
OBJDIR := $(BUILDDIR)/obj

SRCS := $(notdir $(shell find -name '*.c'))
OBJS := $(patsubst %.c, $(OBJDIR)/%.o, $(SRCS))

gpiorca: builddir $(OBJS) $(SRCS) 
	$(LXX) $(LXXFLAGS) $(OBJS) -o $(BUILDDIR)/gpiorca

$(OBJDIR)/%.o: %.c
	$(CXX) $(CXXFLAGS) $^ -o $@

.PHONY: builddir
builddir:
	@mkdir -p $(OBJDIR)

.PHONY: clean
clean:
	@rm -f -r build