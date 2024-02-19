use axum::{
    routing::get,
    Router,
};
#[tokio::main]
async fn main() {
    let app = Router::new().route("/",get(|| async {"hellow, world"}));
    let listener = tokio::net::TcpListener::bind("0.0.0.0:6969").await.unwrap();
    axum::serve(listener, app).await.unwrap();
}
