FOR /L %%A IN (27018,1,27018) DO (
timeout 1
start GoldSrcFakeServer 10000 0 0 %%A
)