# Building on Mac OSX
1. install Xcode and Xcode Command Line Utilites
2. start Xcode, settings -> Locations, activate your Command Line Tools
3. install Qt Creator
4. install brew https://brew.sh/
5. `brew install boost openssl rapidjson`
6. build the project using Qt Creator

If the Project does not build at this point, you might need to add additional Paths/Libs, because brew does not install openssl and boost in the common path. You can get their path using

`brew info openssl`
`brew info boost`

The lines which you need to add to your project file should look similar to this

```
INCLUDEPATH += /usr/local/opt/openssl/include
LIBS += -L/usr/local/opt/openssl/lib

INCLUDEPATH += "/usr/local/Cellar/boost/1.67.0_1/include"
LIBS += -L"/usr/local/Cellar/boost/1.67.0_1/lib"
```