# Generated by using Rcpp::compileAttributes() -> do not edit by hand
# Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

Rinterface <- function(molecule, isotopes, stopCondition, algo = 0L, tabSize = 1000L, hashSize = 1000L, step = .25, showCounts = FALSE, trim = TRUE) {
    .Call('IsoSpecR_Rinterface', PACKAGE = 'IsoSpecR', molecule, isotopes, stopCondition, algo, tabSize, hashSize, step, showCounts, trim)
}

