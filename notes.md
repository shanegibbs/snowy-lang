## Notes

### List Symbols in a Library
```
# nm -gU <lib>
```

### List C++ Symbols
```
# nm -C src/lib/libsnowy.a |c++filt
# objdump -t src/lib/libsnowy.a |c++filt
```

### Flex/Bison References

http://flex.sourceforge.net/manual/Cxx.html

https://github.com/jonathan-beard/simple_wc_example

http://www.mario-konrad.ch/wiki/doku.php?id=programming:flexbison:flexppbisonpp

http://www.epaperpress.com/lexandyacc/index.html
