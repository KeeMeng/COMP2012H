import sublime
import sublime_plugin

class comp2012h_build(sublime_plugin.WindowCommand):
	def run(self, fileio=False):
		vars = self.window.extract_variables()
		file_name = vars["file_name"]
		file_path = vars["file_path"]
		file_base_name = vars["file_base_name"]
		folder = vars["folder"]
		folder_name = folder.split("/")[-1]

		if folder_name == "COMP2012H":
			compiler = "g++ -std=c++11 -Wall -Wextra -pedantic -fsanitize=address,undefined"
			pa_shell_cmd = {
				"pa1":  f"{compiler} -o main main.cpp && ./main",
				"pa2":  f"{compiler} -o main main.cpp && ./main",
				"pa3":  f"{compiler} -o main main.cpp && ./main",
				"pa4":  f"{compiler} -O3 -o main main.cpp && ./main",
				"pa5":  f"{compiler} -o main main.cpp Deque.cpp Deque_Iterator.cpp && ./main",
				"pa6":  f"{compiler} -o main main.cpp Database.cpp String.cpp Table.cpp && ./main",
				# "pa7":  f"cd ../pa7-build-release/app/app.app/Contents/MacOS && ./app",
				"pa8":  f"make main pa8.zip && ./main",
				"pa9":  f"{compiler} -o main main.cpp && ./main",
				"pa10": f"make main && ./main",
				"pa11": f"{compiler} -o main main.cpp node.cpp tasks.cpp dictionary.cpp && ./main"
			}

			for parent in file_path.split("/"):
				if parent in pa_shell_cmd:
					self.window.run_command(
						"terminus_exec", {
							"shell_cmd": f"cd {folder}/{parent} && {pa_shell_cmd[parent]}",
							"focus": True
						}
					)
					break

			else:
				self.window.run_command(
					"terminus_exec", {
						"shell_cmd": f"cd {file_path} && {compiler} -o {file_base_name} {file_name} && ./{file_base_name}",
						"focus": True
					}
				)
