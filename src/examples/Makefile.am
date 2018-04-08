bin_PROGRAMS=CannyDetector example FaceDetection FindObject Smile test SquareDetection DispatcherExample ThreadExample \
	tesscv snap TextDetection1 MagicDatabase

CannyDetector_SOURCES=CannyDetector.cpp
CannyDetector_CPPFLAGS=$(CCGS_CFLAGS)
CannyDetector_LDADD=$(CCGS_LIBS)

example_SOURCES=example.cpp ExampleWindow.cpp ExampleWorker.cpp
example_CPPFLAGS=$(CCGS_CFLAGS)
example_LDADD=$(CCGS_LIBS)

FaceDetection_SOURCES=FaceDetection.cpp
FaceDetection_CPPFLAGS=$(CCGS_CFLAGS)
FaceDetection_LDADD=$(CCGS_LIBS)

FindObject_SOURCES=FindObject.cpp
FindObject_CPPFLAGS=$(CCGS_CFLAGS)
FindObject_LDADD=$(CCGS_LIBS)

Smile_SOURCES=Smile.cpp
Smile_CPPFLAGS=$(CCGS_CFLAGS)
Smile_LDADD=$(CCGS_LIBS)

test_SOURCES=test.cpp
test_CPPFLAGS=$(CCGS_CFLAGS)
test_LDADD=$(CCGS_LIBS)

SquareDetection_SOURCES=SquareDetection.cpp
SquareDetection_CPPFLAGS=$(CCGS_CFLAGS)
SquareDetection_LDADD=$(CCGS_LIBS)

DispatcherExample_SOURCES=DispatcherExample.cpp
DispatcherExample_CPPFLAGS=$(CCGS_CFLAGS)
DispatcherExample_LDADD=$(CCGS_LIBS)

ThreadExample_SOURCES=ThreadExample.cpp
ThreadExample_CPPFLAGS=$(CCGS_CFLAGS)
ThreadExample_LDADD=$(CCGS_LIBS)

tesscv_SOURCES=tesscv.cpp
tesscv_CPPFLAGS=$(CCGS_CFLAGS)
tesscv_LDADD=$(CCGS_LIBS) -ltesseract

snap_SOURCES=snap.cpp
snap_CPPFLAGS=$(CCGS_CFLAGS)
snap_LDADD=$(CCGS_LIBS)

TextDetection1_SOURCES=TextDetection1.cpp
TextDetection1_CPPFLAGS=$(CCGS_CFLAGS)
TextDetection1_LDADD=$(CCGS_LIBS)

MagicDatabase_SOURCES=MagicDatabase.cpp
MagicDatabase_CPPFLAGS=$(CCGS_CFLAGS) -I/usr/include/mysql -I/usr/include/mysql++
MagicDatabase_LDADD=$(CCGS_LIBS) -lmysqlpp -lmysqlclient
