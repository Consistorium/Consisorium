dir = ARGV[0]
from = ARGV[1]
to = ARGV[2]

puts "Renaming occurences of #{from} to #{to} in all files..."

Dir.glob(dir + "*").sort.each do |f|
  filename = File.basename(f, File.extname(f))
  if filename.include? from
    filename.sub! from, to
    File.rename(f, dir + filename + File.extname(f))
  end
end

puts "Renaming complete."
