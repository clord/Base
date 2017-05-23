

add_library(Base
   Blob.cpp
   Date.cpp
   File.cpp
   Internal/MutableBlob.cpp
   Internal/MutableString.cpp
   Vendor/utf8rewind/source/utf8rewind.c
   Vendor/utf8rewind/source/unicodedatabase.c
   Vendor/utf8rewind/source/internal/casemapping.c
   Vendor/utf8rewind/source/internal/codepoint.c
   Vendor/utf8rewind/source/internal/composition.c
   Vendor/utf8rewind/source/internal/database.c
   Vendor/utf8rewind/source/internal/decomposition.c
   Vendor/utf8rewind/source/internal/seeking.c
   Vendor/utf8rewind/source/internal/streaming.c
   MutableBlob.cpp
   MutableString.cpp
   Platform.cpp
   String.cpp
   )
