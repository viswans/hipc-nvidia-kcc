CXXFLAGS := -g -Wall -I include/
#CXXFLAGS = -O2 -DNDebug

EXE := KCC
LDFLAGS := -lm # -L /usr/local/cuda/lib64 -lcuda -lcudart
OBJDIR := obj
SRCDIR := src
SRCTYPE := c

SOURCES := $(wildcard $(SRCDIR)/*.$(SRCTYPE))
OBJECTS := $(patsubst %.$(SRCTYPE),$(OBJDIR)/%.o,$(notdir $(SOURCES)))

.PHONY: clean target

target: all
all: $(EXE)

$(EXE): $(OBJECTS)
	@mkdir -p $(OBJDIR)
	$(CC) -o $(EXE) $(OBJECTS) $(LDFLAGS) 

$(OBJDIR)/%.o: $(SRCDIR)/%.$(SRCTYPE)
	$(CC) $(CXXFLAGS) -c $< -o $@ $(LDFLAGS) 

clean : 
	rm -f $(OBJECTS) $(EXE)

