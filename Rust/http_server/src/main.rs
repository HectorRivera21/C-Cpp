use std::net::TcpListener;

fn main() {
    let listener = TcpListener::bind("127.0.0.1:6969").unwrap();


    println!("Hello, world!");
}
