INCLUDES=-I$(top_srcdir)/include -I$(top_srcdir)/src/solv_smurf/include
sources=  hr_anne.cc hr_anne_update.cc
EXTRA_DIST=hr_choice.cc

#if MYLIBTOOL
#noinst_LTLIBRARIES = libhranne.la # libsolver2.la
#libhranne_la_SOURCES= $(sources)
#libsolver2_la_SOURCES=libsolver.cc
#else
noinst_LIBRARIES = libhranne.a # libsolver2.la
libhranne_a_SOURCES= $(sources)
#noinst_LIBRARIES = libsolver.a libsolver2.a
#libsolver_a_SOURCES= $(sources)
#libsolver2_a_SOURCES=libsolver.cc
#endif

