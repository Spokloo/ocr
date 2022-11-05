DIRS = Images_Processing Images_Transform
MAKE = make

all:
	$(foreach dir,$(DIRS), ${MAKE} -C $(dir);)

clean:
	$(foreach dir,$(DIRS), ${MAKE} clean -C $(dir);)