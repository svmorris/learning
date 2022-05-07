<?php

include "logging.php";


class pwned
{
    public function pwn()
    {
        system($this->command);
    }

}

class ReadFile
{
    public function __toString()
    {
        return file_get_contents($this->filename);
    }
}

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



$obj = unserialize($_POST['fuck']);
// $obj->PrintData();
?>

