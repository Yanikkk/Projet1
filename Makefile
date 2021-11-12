main: Main.cc Env.cpp Env.hpp Matiere.cpp Matiere.hpp Case.cpp Case.hpp Air.cpp Air.hpp Eau.cpp Eau.hpp Sol.cpp Sol.hpp
	g++ -Wall -o "Main" "Main.cc" "Env.cpp" "Matiere.cpp" "Case.cpp" "Air.cpp" "Eau.cpp" "Sol.cpp" -lm
