#Make file, use 'make all'

TARGET = main
OBJDIR = build/obj
CXX = g++
CXX_FLAGS = -std=c++17 -g
LINK_FLAGS = 
COMP_FLAGS = 

all: $(TARGET)

$(TARGET): $(OBJDIR)/main.o $(OBJDIR)/Table.o $(OBJDIR)/Database.o
	$(CXX) $(CXX_FLAGS) $(OBJDIR)/main.o $(OBJDIR)/Table.o $(OBJDIR)/Database.o -o $(TARGET) $(LINK_FLAGS)

$(OBJDIR)/main.o: main.cpp
	$(CXX) $(CXX_FLAGS) -c $< $(COMP_FLAGS) -o $@

$(OBJDIR)/Table.o: Table.cpp
	$(CXX) $(CXX_FLAGS) -c $< $(COMP_FLAGS) -o $@

$(OBJDIR)/Database.o: Database.cpp
	$(CXX) $(CXX_FLAGS) -c $< $(COMP_FLAGS) -o $@


clean:
	-rm -f $(OBJDIR)/*.o
	-rm -f $(TARGET)
