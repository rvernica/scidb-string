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
