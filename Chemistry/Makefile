#
# Copyright (c) 2019-2020    University of Houston. All rights reserved.
# $COPYRIGHT$
#
# Additional copyrights may follow
#
#
include ../Makefile.defs

HEADER = ChemicalFormula.h                \
	ClassExtensions.h                 \
	Constants.h                       \
	Element.h                         \
	Isotope.h                         \
	IsotopicDistribution.h            \
	PeriodicTable.h


OBJ = 	Constants.o                      \
	Element.o                        \
	ClassExtensions.o                \
	ChemicalFormula.o                \
	ClassExtensions.o                \
	Isotope.o                        \
	IsotopicDistribution.o           \
	PeriodicTable.o


.SUFFIXES: .o.cpp

all:    
	cd Interfaces ; $(MAKE) ; cd ..
	$(MAKE) $(MZLIB_LIB) 


$(MZLIB_LIB): $(HEADER) $(OBJ) 
	$(AR) $(AR_FLAGS) $(MZLIB_LIB_DIR)/$(MZLIB_LIB) $(OBJ)

$(OBJ):	$(HEADER)
.cpp.o:	$(HEADER)
	$(CXX) $(CXXFLAGS) -c $<

clean:  
	cd Interfaces ; $(MAKE) clean ; cd ..
	rm -rf *.o *~
