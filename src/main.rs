fn lex(path: &str) {
}

#[non_exhaustive]
enum Foo {
    A = 0,
}

fn main() {
    let mut args = std::env::args();
    while let Some(arg) = args.next() {
        dbg!(arg.as_str());
        match arg.as_str() {
            "-main_source_file" => {
                let content_arg = Some(args.next());
            },
            _ => {
                let content_arg = Some(args.next());
            },
        }
    }
}
