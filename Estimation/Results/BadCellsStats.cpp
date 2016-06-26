#include "BadCellsStats.h"

namespace Estimation
{
	namespace Results
	{
		BadCellsStats::BadCellsStats(const Stats &stats, const Stats::ss_cnt_t &genes_reads, const Stats::ss_cnt_t &genes_umis)
				: genes_reads(genes_reads)
				, genes_umis(genes_umis)
				, cell_exone_reads_per_chr(stats.get_raw_cell_stat(Stats::EXONE_READS_PER_CHR_PER_CELL))
				, cell_nonexone_reads_per_chr(stats.get_raw_cell_stat(Stats::NON_EXONE_READS_PER_CHR_PER_CELL))
				, reads_per_umig(stats.get_raw_cell_stat(Stats::READS_PER_UMIG_PER_CELL))
				, reads_per_umi(stats.get_raw_cell_stat(Stats::READS_PER_UMI_PER_CELL))
				, merges_count(stats.get_raw_stat(Stats::MERGES_COUNT))
		{}

#ifdef R_LIBS
		void BadCellsStats::save_r_table(const std::string &filename) const
		{
			using namespace Rcpp;

			L_TRACE << "writing R data to " << filename;
			RInside *R = RInside::instancePtr();
			if (R == nullptr)
			{
				R = new RInside(0, 0);
			}

			(*R)["genes_reads"] = this->genes_reads;
			(*R)["genes_umis"] = this->genes_umis;
			(*R)["cell_exone_reads_per_chr"] = this->cell_exone_reads_per_chr;
			(*R)["cell_nonexone_reads_per_chr"] = this->cell_nonexone_reads_per_chr;
			(*R)["reads_per_umig"] = this->reads_per_umig;
			(*R)["reads_per_umi"] = this->reads_per_umi;

			(*R)["merges_count"] = this->merges_count;

			R->parseEval("d <- list(genes_reads=genes_reads, genes_umis=genes_umis, cell_exone_reads_per_chr=cell_exone_reads_per_chr, "
								 "cell_nonexone_reads_per_chr=cell_nonexone_reads_per_chr, merges_count=merges_count,"
								 "reads_per_umig=reads_per_umig, reads_per_umi=reads_per_umi)");

			R->parseEvalQ("saveRDS(d, '" + filename + "')");
			L_TRACE << "Done";
		}
#endif
	}
}