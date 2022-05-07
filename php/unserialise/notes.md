A short demonstration of how php serialization works
====================================================

An example class
```php
class User
{
    public $username;
    public $isAdmin;

    public function PrintData()
    {
        if ($this->isAdmin)
        {
            echo $this->username . " is admin\n";
        }
        else
        {
            echo $this->username . " is not admin\n";
        }
    }
}
```


Calling the object I set the username to `fuck` and the `isAdmin` attribute to True:
```
$obj = new User();
$obj->username = "fuck";
$obj->isAdmin = True;
```


Then calling serialize to show what the object looks like when serialised.
```
echo serialize($obj);
```


A serialised object
```
O:4:"User":2:{s:8:"username";s:4:"fuck";s:7:"isAdmin";b:1;}
```

The following are the meanings of each element in the serialised object
`O:` -- type of element.
    o == object
    s == string
    i == integer
    b == boolian


`4:` -- Length of the object name


`User:` -- Name of the object (class)


`2:` -- the number of attributes the object has
    - username
    - isAdmin




First attribute:
```
s:8:"username";s:4:"fuck";
```

`s:` -- variable name is a string
`8:` -- 8 chars in the variable name
`s:` -- value is a string
`4:` -- 4 chars in the value


Second attribute:
```
s:7:"isAdmin";b:1;
```
`s:` -- variable name is a string
`7:` -- variable name is 7 chars
`b:` -- value is a boolian
`1:` -- boolian is true



Abuse
-----

This all can be abused when you get to serializing objects.

When an object is serialized, only the object name and attributes are saved, but nothing else. PHP expects the object to exist when it is deserialised, thus it doesn't need to serialise methods and such.

What this means in practice is that we can get the program to unserialize any object that exists within scope at the time of deserialising, but we cannot include our own code in the objects.

This can still be exploitable with "magic methods". These are methods that get called without you explicitly calling them. Such methods include `__toString`, `__construct` and `__destruct`.

#### Exploit setup:
Say for example there is a method that writes a file. It takes both the filename and the contents from attribute variables.
```php
class LogFile
{
    public function __destruct()
    {
        file_put_contents($this->filename, $this->username, FILE_APPEND);
    }
}
```
In the example this is done from within the destructor.

In our serialized object, instead of any normal variable like `username` or `userId`, we can just have an object that points to this `LogFile` class and has the attributes of `$filename` and `$username` set to something malicious. (like a php script).

After deserialising, if this variable goes out of scope, or get overwritten, php will call the destructor and the function will write our malicious code.


This is called a gadget
