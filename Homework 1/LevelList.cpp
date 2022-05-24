#include "LevelList.h"
#include "Sequence.h"

LevelList::LevelList() {
	SeqLevel = 0;
}

bool LevelList::add(unsigned long level) {
	if (level < 30 || level > 400 || SeqLevel >= DEFAULT_MAX_ITEMS)
		return false;
	else {
		if (levels.insert(SeqLevel, level) != -1) {
			SeqLevel++;
			return true;
		}
		else
			return false;
	}
}

bool LevelList::remove(unsigned long level) {
	if (levels.find(level) != -1) {
		int i = levels.find(level);
		if (levels.erase(i) == true) {
			SeqLevel--;
			return true;
		}
	}
	return false;
}

int LevelList::size() const {
	return SeqLevel;
}

unsigned long LevelList::minimum() const {
	if (SeqLevel == 0)
		return NO_LEVEL;
	else {
		unsigned long holder, min;
		levels.get(0, min);
		for (int i = 0; i <= levels.size(); i++) {
			levels.get(i, holder);
			if (holder < min)
				min = holder;
		}
		return min;
	}
}

unsigned long LevelList::maximum() const {
	if (SeqLevel == 0)
		return NO_LEVEL;
	else {
		unsigned long holder, max;
		levels.get(0, max);
		for (int i = 0; i <= levels.size(); i++) {
			levels.get(i, holder);
			if (holder > max)
				max = holder;
		}
		return max;
	}

}