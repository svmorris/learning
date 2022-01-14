use std::io;
use std::io::Write;
use rand::Rng;

fn main() {
    print!("guess something dummy: ");

    let mut guess = String::new();
    let random_number = rand::thread_rng().gen_range(0, 100);


    io::stdout()
        .flush()
        .unwrap();


    io::stdin()
        .read_line(&mut guess)
        .expect("sorry fella, read_line failed");


    let guess_num: u32 = guess
        .trim()
        .parse()
        .expect("Not a number");


    if random_number == guess_num
    {
        println!("damn bro you arent useless after all");
    }
    else
    {
        println!("damn useless piece of shit\nThe correct answer was {}", random_number);
    }

}
