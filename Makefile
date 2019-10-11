all:
	@echo "Please, use 'make ball' or 'make robot'"

ball:
	$(MAKE) -C Ball

robot:
	$(MAKE) -C RobotArm
