BufWrL : UGen {
	*ar { |bufNum, phase, sample|
		^this.multiNew('audio', bufNum, phase, sample);
	}
}
