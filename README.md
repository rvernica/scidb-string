# String

Functions for manipulating strings

## Concatenate

```
$ iquery --afl --query "store(build(<s:string>[i=0:1,2,0], '[(\'foo\'), (\'BAR\')]', true), sample)"
{i} s
{0} 'foo'
{1} 'BAR'

$ iquery --afl --query "apply(sample, r, s + 'Taz')"
{i} s,r
{0} 'foo','fooTaz'
{1} 'BAR','BARTaz'
```

Concatenate allows concatenating strings with other numeric types. The supported types are: `int8`, `int16`, `int32`, `int64`, `uint8`, `uint16`, `uint32`, `uint64`, `float`, and `double`.
```
$ iquery --afl --query "store(build( \
    <s:string, \
     i8:int8,  i16:int16,  i32:int32,  i64:int64, \
     u8:uint8, u16:uint16, u32:uint32, u64:uint64, \
     f:float,  d:double>[i=0:1,2,0], \
    '[(\'foo\', -8, -16, -32, -64, 8, 16, 32, 64, 3.2, 6.4),
      (\'BAR\', -1, -2, -3, -4, 1, 2, 3, 4, 1.2, 3.4)]', \
    true), sample2)"
{i} s,i8,i16,i32,i64,u8,u16,u32,u64,f,d
{0} 'foo',-8,-16,-32,-64,8,16,32,64,3.2,6.4
{1} 'BAR',-1,-2,-3,-4,1,2,3,4,1.2,3.4

$ iquery --afl --query "apply(sample2,
    r, s + i8 + i16 + i32 + i64 + u8 + u16 + u32 + u64 + f + d + 'Taz' + 99 + 0.88)"
{i} s,i8,i16,i32,i64,u8,u16,u32,u64,f,d,r
{0} 'foo',-8,-16,-32,-64,8,16,32,64,3.2,6.4,'foo-8-16-32-6481632643.200000056.4000000000000004Taz990.88'
{1} 'BAR',-1,-2,-3,-4,1,2,3,4,1.2,3.4,'BAR-1-2-3-412341.200000053.3999999999999999Taz990.88'
```

## Lowercase/Uppercase

```
$ iquery --afl --query "store(build(<s:string>[i=0:1,2,0], '[(\'foo\'), (\'BAR\')]', true), sample)"
{i} s
{0} 'foo'
{1} 'BAR'

$ iquery --afl --query "apply(sample, r, strlower(s))"
{i} s,r
{0} 'foo','foo'
{1} 'BAR','bar'

$ iquery --afl --query "apply(sample, r, strupper(s))"
{i} s,r
{0} 'foo','FOO'
{1} 'BAR','BAR'
```

## Trim

Remove leading or trailing spaces.
```
$ iquery --afl --query "store(build(<s:string>[i=0:1,2,0], '[(\'foo  \'), (\' BAR \')]', true), sample)"
{i} s
{0} 'foo  '
{1} ' BAR '

$ iquery --afl --query "apply(sample, r, strtrim(s))"
{i} s,r
{0} 'foo  ','foo'
{1} ' BAR ','BAR'
```

## Installation

The easiest way is to first set up
[dev_tools](https://github.com/paradigm4/dev_tools). Once `dev_tools`
are installed and loaded, use:
```
$ iquery --afl --query "install_github('rvernica/scidb-string')"
```

If if want to install a different revision or specify a proxy, use:
```
$ iquery --afl --query "install_github('rvernica/scidb-string', 'master', 'https_proxy=https://...')"
```

To load the library, use:
```
$ iquery --afl --query "load_library(string)"
```
