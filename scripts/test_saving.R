filename <- tempfile()
df <- data.frame(x = c(1, 2), y = c(3, 4))
write.csv(x = df, file = filename, row.names = FALSE, eol = "\n")
lines <- readLines(filename)
df_again <- read.csv(filename)
testthat::expect_equal(df, df_again)

# Writing
writeLines(text = lines, con = filename)
df_again <- read.csv(filename)
testthat::expect_equal(df, df_again)

# Writing with added comments
comment_lines <- c("# Comment", "# Another comment", lines)
writeLines(text = comment_lines, con = filename)
df_again <- read.csv(filename, comment.char = "#")
testthat::expect_equal(df, df_again)
