#include <c2b.h>

int main(int argc, char** argv) {
    c2b::Build::rebuild_self(argc, argv, __FILE__);
    c2b::Build build("main");

    build.append_include_dir("include");
    build.append_source_dir("src");
    build.append_flag("ggdb");

    return build.build_and_run("-amount", "100", "-msg", "\"Hello, World!\"", "-price", "500.25", "-tax", "0.08");
}
