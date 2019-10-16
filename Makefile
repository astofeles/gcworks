all:
	@echo "Please, run one of the following"
	@echo "'make ball', 'make robot' or 'make maze'"

ball:
	$(MAKE) -C Ball

robot:
	$(MAKE) -C RobotArm

maze:
	$(MAKE) -C Maze
