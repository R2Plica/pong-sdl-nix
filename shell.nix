{ pkgs ? import <nixpkgs> {}}:

pkgs.mkShell {
  name = "pong-sdl-nix";
  nativeBuildInputs = with pkgs; [pkg-config cmake];
  buildInputs = with pkgs; [
    imgui
    boost
    SDL2
    glfw
  ];
  IMGUI_DIR = "${pkgs.imgui}/include/imgui";
  shellHook = ''
          cd build
          cmake ..
          cmake --build .
          cd ..
  '';
}