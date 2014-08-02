table <- read.table("problem3.tmp")

data <- cbind(table[2], table[3])
data[1] <- data[1] / max(data[1])
data[2] <- data[2] / max(data[2])
rownames(data) <- t(table[1])
n <- length(row(data))

limit <- sqrt(n)
if (limit > 10) limit = 10


last <- kmeans(data, 1, nstart = 10)$tot.withinss
gaps <- NULL
print(last)
for (i in 2:limit) {
    print("running... I'm alive... please be patient...")
    now <- kmeans(data, i, nstart = i * i * 20)$tot.withinss
    print(now)
    gap <- last / now
    gaps <- c(gaps, gap)
    print(gaps)
    last <- now
}

print("done..........")
result <- kmeans(data, which.max(gaps) + 1, nstart = 1000)
write.table(result$cluster, file = "problem3.tmp.out")
