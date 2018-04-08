bin_PROGRAMS=scanner

scanner_SOURCES=CCG_Scanner-gtk2.cpp MainWindow.cpp Picture.cpp CardLibrary.cpp Card.cpp CardScanner.cpp
scanner_CPPFLAGS=$(CCGS_CFLAGS) -I/usr/include/tesseract -I/usr/include/mysql -I/usr/include/mysql++
scanner_LDADD=$(CCGS_LIBS) -ltesseract -lmysqlpp -lmysqlclient
