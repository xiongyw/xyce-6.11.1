ADMSDIR=../..

XyceADMSFILES = $(ADMSDIR)/xyceVersion.xml \
        $(ADMSDIR)/xyceBasicTemplates.xml \
        $(ADMSDIR)/xyceHeaderFile.xml \
        $(ADMSDIR)/xyceImplementationFile.xml


all-source: N_DEV_ADMShic0_full.C

clean:
	rm -f N_DEV_ADMShic0_full.C *.o *.so*

N_DEV_ADMShic0_full.C: hicumL0V1p32.va  $(XyceADMSFILES)
	admsXml  -e $(ADMSDIR)/xyceVersion.xml -e $(ADMSDIR)/xyceBasicTemplates.xml -e $(ADMSDIR)/xyceHeaderFile.xml -e $(ADMSDIR)/xyceImplementationFile.xml hicumL0V1p32.va
	emacs N_DEV_ADMShic0_full.C --batch --eval="(require 'cc-mode)" --eval="(c-set-offset 'substatement-open 0)" --eval="(c-set-offset 'arglist-intro 3)" --eval="(c-set-offset 'innamespace -2)" --eval="(setq-default indent-tabs-mode nil)" --eval='(indent-region (point-min) (point-max) nil)' -f save-buffer
	emacs N_DEV_ADMShic0_full.h --batch --eval="(require 'cc-mode)" --eval="(c-set-offset 'substatement-open 0)" --eval="(c-set-offset 'arglist-intro 3)" --eval="(c-set-offset 'innamespace -2)" --eval="(setq-default indent-tabs-mode nil)" --eval='(indent-region (point-min) (point-max) nil)' -f save-buffer

