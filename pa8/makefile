# Definition of variables
CPPFLAGS = -std=c++11 -g
SRCS = main.cpp GameUI.cpp GameEngine.cpp MapUnit.cpp Terrains/Terrain.cpp Terrains/Wall.cpp Terrains/Grass.cpp Terrains/EmptyLand.cpp Items/Item.cpp Items/Gem.cpp Items/Book.cpp Items/Medicine.cpp Monsters/Monster.cpp Monsters/Zombie.cpp Monsters/Warlock.cpp Monsters/ShadowPriest.cpp Player/Player.cpp Player/Mage.cpp Player/Warrior.cpp Player/Archer.cpp
SUB = GameEngine.cpp Terrains/Terrain.cpp Terrains/Wall.cpp Terrains/Grass.cpp Terrains/EmptyLand.cpp Items/Item.cpp Items/Gem.cpp Items/Book.cpp Items/Medicine.cpp Monsters/Monster.cpp Monsters/Zombie.cpp Monsters/Warlock.cpp Monsters/ShadowPriest.cpp Player/Mage.cpp Player/Warrior.cpp Player/Archer.cpp
OBJS = $(SRCS:.cpp=.o)
EXE = main
ZIP = pa8.zip

ifeq (Windows_NT, $(OS))
RM_CMD := cmd //C del
ZIP_CMD := zip.exe
else
RM_CMD := rm -vf
ZIP_CMD :=zip
endif

.PHONY: all
all: $(EXE) $(ZIP)

$(EXE): $(OBJS)
	g++ $(CPPFLAGS) -o $@ $(OBJS)

$(ZIP): $(SUB)
	$(RM_CMD) $(ZIP)
	$(ZIP_CMD) $@ $^

%.o: %.cpp
	g++ $(CPPFLAGS) -c $< -o $@

# For removing the objects/executable files
clean:
	rm -vf $(OBJS) $(ZIP)
# makedepend can find the .h dependencies automatically
depend:
	g++ -MM $(SRCS)
