## sub directory

routing_SOURCES = \
	DistanceRoutingExtension.cpp \
	DistanceRoutingExtension.h \
	ContentStorage.cpp \
	ContentStroage.h \
	ContentStorageEntry.cpp \
	ContentStorageEntry.h \
	DistanceEntry.cpp \
	DistanceEntry.h \
	DistanceTable.h \
	DistanceTable.cpp \
	PendingInterestEntry.cpp \
	PendingInterestEntry.h \
	PendingInterestTable.cpp \
	PendingInterestTable.h \
	DataEmTs.cpp \
	DataEmTs.h 
	
AM_CPPFLAGS = -I$(top_srcdir)/src $(ibrdtn_CFLAGS)
AM_LDFLAGS = $(ibrdtn_LIBS)

if ANDROID
noinst_DATA = Android.mk
CLEANFILES = Android.mk
else
noinst_LTLIBRARIES = librtdistance.la
librtdistance_la_SOURCES= $(routing_SOURCES)
endif

Android.mk: Makefile.am
	$(ANDROGENIZER) -:PROJECT dtnd \
		-:REL_TOP $(top_srcdir) -:ABS_TOP $(abs_top_srcdir) \
		-:STATIC libdtnd_rtflooding \
		-:SOURCES $(routing_SOURCES) \
		-:CPPFLAGS $(CPPFLAGS) $(AM_CPPFLAGS) \
		-:LDFLAGS $(AM_LDFLAGS) \
		> $@
